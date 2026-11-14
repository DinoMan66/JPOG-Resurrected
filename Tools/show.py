#!/usr/bin/env python3
"""
show.py - everything about one function in one command: tracker/attempts rows, Ghidra's C and the annotated
disassembly (calls, imports, strings resolved). Ported from ZooTycoonDecompiled\\Tools\\show.py.

Usage:  python show.py <Dll> <name-substring | rva> [--asm-only | --c-only]
        python show.py TRenderInterface ?Create@TMaterialLibrary
        python show.py SimJP 0x2f6aa0
<Dll> is the file name without _inst/.dll (TRenderInterface, TSkinShaderD3D, SimJP). Several matches -> a list.
Run from anywhere; reads Original\\, Notes\\function_tracker.csv, Notes\\attempts.csv, decompiled\\<file>.c.
Accepts Class::method (also ctors/dtors) as well as parts of decorated names; up to four matches are all shown.
Needs capstone or GNU objdump.
"""
import os as _os, sys as _sys
# the standard 'dis' (and capstone, which needs it) must load before Tools\dis.py can hide it
_HERE = _os.path.dirname(_os.path.abspath(__file__))
_sys.path[:] = [_p for _p in _sys.path if _os.path.abspath(_p or ".") != _HERE]
import inspect, dis  # noqa: E401,F401
try:
    import capstone
except Exception:
    capstone = None
import bisect, csv, glob, importlib.util, os, re, subprocess, sys
sys.path.insert(0, _HERE)
import compare as C
_spec = importlib.util.spec_from_file_location("dis_tool", os.path.join(_HERE, "dis.py"))
DI = importlib.util.module_from_spec(_spec); _spec.loader.exec_module(DI)


def disassemble(path, d, r2o, base, start, stop):
    """-> [(va, text)] with capstone, else GNU objdump"""
    if capstone is not None:
        o = r2o(start - base)
        if o is not None:
            cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
            return [(i.address, f"{i.mnemonic} {i.op_str}".strip()) for i in cs.disasm(d[o:o + (stop - start)], start)]
    try:
        out = subprocess.run(["objdump", "-d", "-M", "intel", "--no-show-raw-insn", f"--start-address={start:#x}",
                              f"--stop-address={stop:#x}", path], capture_output=True, text=True).stdout
    except FileNotFoundError:
        sys.exit("no disassembler: install capstone (py -m pip install capstone) or GNU objdump")
    rows = []
    for ln in out.splitlines():
        m = re.match(r"\s*([0-9a-f]+):\s*(.*)", ln)
        if m: rows.append((int(m.group(1), 16), m.group(2)))
    return rows


def to_pattern(what):
    """Class::method / Class::Class / Class::~Class -> the matching part of a decorated name"""
    m = re.match(r"^(?:\w+::)*?(\w+)::(~?)(\w+)$", what)
    if not m:
        return what
    cls, tilde, meth = m.groups()
    if meth == cls:
        return f"??{'1' if tilde else '0'}{cls}@"
    return f"?{meth}@{cls}@"

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def find_binary(name):
    for p in glob.glob(os.path.join(ROOT, "Original", "**", "*.*"), recursive=True):
        b = os.path.basename(p)
        if b.lower().endswith((".dll", ".exe")) and \
                os.path.splitext(b.replace("_inst", ""))[0].lower() == name.lower():
            return p
    sys.exit(f"no binary called {name} under Original\\")


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    dll, what, opts = sys.argv[1], sys.argv[2], sys.argv[3:]
    path = find_binary(dll)
    d = open(path, "rb").read()
    base, secs, r2o, imp = DI.imports(d)
    _, _, exports, code = C.load_dll(path)
    byrva = {r: n for n, r in exports.items()}
    if re.match(r"^(0x)?[0-9a-fA-F]+$", what):
        rva = int(what, 16)
        rva = rva - base if rva >= base else rva
    else:
        pat = to_pattern(what)
        hits = sorted((r, n) for n, r in exports.items() if pat.lower() in n.lower())
        if not hits and pat != what:
            hits = sorted((r, n) for n, r in exports.items() if what.lower() in n.lower())
        if not hits:
            words = [w for w in re.split(r"\W+", what) if len(w) > 2]
            near = sorted((r, n) for n, r in exports.items() if words and all(w.lower() in n.lower() for w in words))
            print(f"no export of {os.path.basename(path)} matches '{what}' (looked for '{pat}')")
            for r, n in near[:15]: print(f"  similar: {r:#07x}  {n}")
            sys.exit(1)
        if len(hits) > 4:
            print(f"{len(hits)} matches - give more of the name or the rva:")
            for r, n in hits[:30]: print(f"  {r:#07x}  {n}")
            return
        if len(hits) > 1:                                    # a few overloads: show all of them, saves a round trip
            print(f"{len(hits)} matches - showing all of them")
            for r, n in hits:
                sys.argv = [sys.argv[0], dll, f"{r:#x}"] + opts
                main(); print()
            return
        rva = hits[0][0]
    name = byrva.get(rva, f"sub_{base + rva:x}")
    print(f"== {os.path.basename(path)}  rva {rva:#x}  va {base + rva:#x}  {name}")
    key = os.path.basename(path).replace("_inst", "").lower()
    size = None
    for f, cols in (("function_tracker.csv", None), ("attempts.csv", None)):
        p = os.path.join(ROOT, "Notes", f)
        if os.path.exists(p):
            for r in csv.DictReader(open(p, newline="", encoding="utf-8", errors="replace")):
                if (r.get("decorated_name") == name or r.get("name") == name) and \
                        (not r.get("dll") or r["dll"].lower() == key):
                    print(f"{f}: " + ", ".join(f"{k}={v}" for k, v in r.items() if v))
                    if r.get("max_size_bytes"): size = int(r["max_size_bytes"])
    if "--asm-only" not in opts:
        cf = os.path.join(ROOT, "decompiled", os.path.basename(path) + ".c")
        if os.path.exists(cf):
            txt = open(cf, encoding="utf-8", errors="replace").read()
            m = re.search(r"\n// ==== 0*%x  .*\n" % (base + rva), txt, re.I)
            if m:
                end = txt.find("\n// ==== ", m.end())
                print(txt[m.start():end if end > 0 else None].rstrip())
            else:
                print(f"(no Ghidra function at {base + rva:#x} in decompiled\\{os.path.basename(cf)})")
        else:
            print(f"(no decompiled\\{os.path.basename(path)}.c - run Tools\\export_decompiled.bat)")
    if "--c-only" in opts:
        return
    starts = sorted(set(r for r in exports.values()))
    i = bisect.bisect_right(starts, rva)
    stop = starts[i] if i < len(starts) else rva + 0x1000
    stop = min(stop, rva + (size or 0x1000))
    def strat(a):
        o = r2o(a - base)
        if o is None: return None
        s = d[o:o + 80].split(b"\0")[0]
        return '"%s"' % s.decode() if len(s) >= 3 and all(32 <= c < 127 for c in s) else None
    names = {base + r: n for n, r in exports.items()}
    for a, ins in disassemble(path, d, r2o, base, base + rva, base + stop):
        notes = []
        for h in re.findall(r"0x([0-9a-f]{6,8})", ins):
            v = int(h, 16)
            if v in imp: notes.append(imp[v])
            elif v in names: notes.append(names[v])
            else:
                o = r2o(v - base)
                if o is not None and d[o:o + 2] == b"\xff\x25":
                    notes.append("-> " + imp.get(int.from_bytes(d[o + 2:o + 6], "little"), "?"))
                else:
                    s = strat(v)
                    if s: notes.append(s)
        print(f"{a - base:08x}: {ins}" + (("    ; " + ", ".join(notes)) if notes else ""))


if __name__ == "__main__":
    main()
