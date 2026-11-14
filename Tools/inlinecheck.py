#!/usr/bin/env python3
"""
inlinecheck.py - functions we call out of line that the original never calls: probably inline in the original.
Free tool (Tools\\TOOLS.md), both projects.

The method found most of JPOG's missing inlines (MATCHING_NOTES "Header inlines and call-site evidence"): take every
call our build makes to a function whose address is known, and count the calls to that address in the original.
None at all means the original has the body pasted into its callers, i.e. the function is an inline (in-class or
`inline`) there - or, in Zoo Tycoon, a tiny out-of-line helper that BBT pasted into every caller (MATCHING_NOTES 95:
then keep it out of line). Either way the calling functions cannot match while we call it.

    python3 -I Tools/inlinecheck.py                       report: Notes\\inline_candidates.md   (py Tools\\inlinecheck.py on the PC)
    python3 -I Tools/inlinecheck.py --results <dir>       another build (JPOG: a folder with ALL.txt or unbundled files)

Columns: the function, its address, how many of our functions call it, and how often the original refers to its
address without calling it (vtable slots, function pointers: a virtual function that is also called directly).
A hint list, not evidence: check each against the original's callers before changing a header.
"""
import os as _os, sys as _sys
_sys.path[:] = [_p for _p in _sys.path if _os.path.abspath(_p or ".") != _os.path.dirname(_os.path.abspath(__file__))]
import inspect, dis  # noqa: E401,F401  (the standard modules first: Tools\dis.py must not hide them)
import argparse, collections, glob, os, re, struct, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
ZOO = os.path.exists(os.path.join(ROOT, "Original", "zoo.exe"))
REL32 = 0x14


def tools():
    sys.path.insert(0, HERE)
    import symcheck as SC
    return SC


def read_map(path, base):
    out = []
    if os.path.exists(path):
        for ln in open(path, errors="replace"):
            ln = ln.split("#", 1)[0].strip()
            if "=" in ln:
                k, v = ln.rsplit("=", 1)
                try: v = int(v.strip(), 0)
                except ValueError: continue
                out.append((k.strip(), v if v >= base else v + base))
    return out


def references(pe):
    """-> (Counter of call/jmp rel32 targets in the code sections, Counter of address-like 4-byte values anywhere)"""
    calls, ptrs = collections.Counter(), collections.Counter()
    d = pe.d
    peo = struct.unpack_from("<I", d, 0x3c)[0]
    nsec = struct.unpack_from("<H", d, peo + 6)[0]
    so = peo + 24 + struct.unpack_from("<H", d, peo + 20)[0]
    lo, hi = pe.base, pe.base + pe.size
    for i in range(nsec):
        h = so + 40 * i
        vs, va, rs, rp = struct.unpack_from("<IIII", d, h + 8)
        code = struct.unpack_from("<I", d, h + 36)[0] & 0x20000000
        blob = d[rp:rp + rs]
        base = pe.base + va
        n = len(blob) - 4
        if code:
            for j in range(n):
                if blob[j] in (0xE8, 0xE9):
                    t = (base + j + 5 + struct.unpack_from("<i", blob, j + 1)[0]) & 0xFFFFFFFF
                    if lo <= t < hi: calls[t] += 1
        for j in range(n + 1):
            v = struct.unpack_from("<I", blob, j)[0]
            if lo <= v < hi: ptrs[v] += 1
    return calls, ptrs


def pretty(sym):
    m = re.match(r"\?\?([0-9]|_[0-9A-Z])([^@]+)@", sym)
    if m:
        code, cls = m.groups()
        return {"0": f"{cls}::{cls}", "1": f"{cls}::~{cls}", "4": f"{cls}::operator="}.get(code, sym)
    m = re.match(r"\?([^@?]+)@([^@]+)@", sym)
    return f"{m.group(2)}::{m.group(1)}" if m else sym.lstrip("_")


def zoo(resdir, SC):
    sys.path.insert(0, HERE)
    import compare as C
    pe = SC.PEInfo(os.path.join(ROOT, "Original", "zoo.exe"))
    pats = read_map(os.path.join(ROOT, "Notes", "zoo.map"), pe.base) + read_map(os.path.join(ROOT, "Notes", "symbols.map"), pe.base)
    res = SC.Resolver(pe, pats, SC.zoo_multi(os.path.join(ROOT, "Notes", "zoo.map"), pe))
    callers = collections.defaultdict(set)
    for p in sorted(glob.glob(os.path.join(resdir, "*.obj"))):
        b = os.path.basename(p)
        if ".Var" in b or b.startswith("zzperm."): continue
        try: o = C.Obj(p)
        except Exception: continue
        for k, (sec, val, name) in enumerate(o.funcs):
            _, s, e = o.func_bytes(k)
            for a, (si, t) in o.sections[sec]["rels"].items():
                if s <= a < e and t == REL32:
                    sym = o.syms.get(si, ("",))[0]
                    if sym and sym != name and not sym.startswith("__imp_"):
                        callers[sym].add(name)
    return pe, res, callers, {}


def jpog(resdir, SC):
    tmp = None
    allp = os.path.join(resdir, "ALL.txt")
    if os.path.exists(allp) and not glob.glob(os.path.join(resdir, "*.rel")):
        tmp = tempfile.mkdtemp(prefix="inlinecheck_")
        cur, buf = None, []
        def flush():
            if cur and cur.endswith(".rel"):
                open(os.path.join(tmp, cur), "w", encoding="latin1", newline="").write("".join(buf))
        for ln in open(allp, encoding="latin1", newline=""):
            if ln.startswith("##FILE "): flush(); cur, buf = ln[7:].strip(), []
            else: buf.append(ln)
        flush(); resdir = tmp
    originals = {}
    for p in glob.glob(os.path.join(ROOT, "Original", "**", "*.dll"), recursive=True) + glob.glob(os.path.join(ROOT, "Original", "*.exe")):
        b = os.path.basename(p).replace("_inst", "").replace(".dll", "").replace(".exe", "")
        if b not in originals or "_inst" in p: originals[b] = p
    per_dll = collections.defaultdict(lambda: collections.defaultdict(set))
    for rp in sorted(glob.glob(os.path.join(resdir, "*.rel"))):
        b = os.path.basename(rp)
        dll = b.split(".")[0]
        if dll == "zzperm" or b.split(".")[1].startswith("Var"): continue
        for fname, lst in SC.jpog_relocs(rp).items():
            for off, typ, add, sym in lst:
                if typ == REL32 and sym != fname and not sym.startswith("__imp_"):
                    per_dll[dll][sym].add(fname)
    return originals, per_dll


def matched_names():
    p = os.path.join(ROOT, "Notes", "verified_functions.csv")
    if not os.path.exists(p): return set()
    import csv
    return {r["name"] for r in csv.DictReader(open(p, newline="", encoding="utf-8", errors="replace")) if r["status"] == "MATCH"}


def report(rows, unknown, out, title):
    rows.sort(key=lambda r: (-len(r[3]), r[0]))
    L = [f"# Inline candidates{title}", "",
         "Functions our build calls out of line whose address the original NEVER calls (Tools/inlinecheck.py).",
         "Most are inline in the original (in-class or `inline`): make them inline and the callers can match. In Zoo",
         "Tycoon a tiny helper can also be out of line but pasted into every caller by BBT (MATCHING_NOTES 95) -",
         "check one caller in the original before changing anything. A hint list, not evidence.", "",
         "Only callees with at least one caller that does not match yet are listed.", "",
         "| Function | Address | Our callers (not matching) | Original: other references | Called by (ours, not matching) |", "|---|---|---:|---:|---|"]
    for sym, va, ptrs, users, where in rows:
        L.append(f"| `{pretty(sym)}` | {where}{va:#x} | {len(users)} | {ptrs} | "
                 + ", ".join(pretty(u) for u in sorted(users)[:3]) + (" ..." if len(users) > 3 else "") + " |")
    L += ["", f"{unknown} called symbols have no known address yet (not in the maps / exports): not checked."]
    open(out, "w", encoding="utf-8", newline="\n").write("\n".join(L) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--results", help="build folder (default Results)")
    a = ap.parse_args()
    SC = tools()
    resdir = a.results or os.path.join(ROOT, "Results")
    out = os.path.join(ROOT, "Notes", "inline_candidates.md")
    rows, unknown, checked = [], 0, 0
    done = matched_names()          # a callee whose callers all match already is fine as it is (BBT-pasted helpers in Zoo)
    if ZOO:
        pe, res, callers, _ = zoo(resdir, SC)
        calls, ptrs = references(pe)
        for sym, users in callers.items():
            va = res.address(sym)
            if va is None: unknown += 1; continue
            checked += 1
            open_users = {u for u in users if u not in done}
            if calls.get(va, 0) == 0 and open_users:
                rows.append((sym, va, ptrs.get(va, 0), open_users, ""))
        report(rows, unknown, out, " - zoo.exe")
    else:
        originals, per_dll = jpog(resdir, SC)
        for dll, callers in sorted(per_dll.items()):
            if dll not in originals: continue
            pe = SC.PEInfo(originals[dll])
            res = SC.Resolver(pe, read_map(os.path.join(ROOT, "Notes", dll + ".map"), pe.base))
            calls, ptrs = references(pe)
            for sym, users in callers.items():
                va = res.address(sym)
                if va is None: unknown += 1; continue
                checked += 1
                open_users = {u for u in users if u not in done}
                if calls.get(va, 0) == 0 and open_users:
                    rows.append((sym, va - pe.base, ptrs.get(va, 0), open_users, f"{dll} "))
        report(rows, unknown, out, "")
    print(f"{checked} called functions checked: {len(rows)} never called by the original -> Notes\\inline_candidates.md"
          f" ({unknown} without a known address)")


if __name__ == "__main__":
    main()
