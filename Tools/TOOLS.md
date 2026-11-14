# Tools - Jurassic Park: Operation Genesis

Every tool in `Tools\`, what it does and whether it is **free** (improve it directly) or **protected**
(changes only through `Tools\proposed\<name>\` + the user's `anticheat.py trial/accept`; CLAUDE.md rule 3 and
"Improving the setup"). Add a line when you add a tool; log every change in `Tools\CHANGES.md`.
Python tools run with `python3 -I Tools/<tool>.py ...` on Claude's side or `py Tools\<tool>.py ...` on the PC.

## Protected - decide what counts

| Tool | What it does |
|---|---|
| `compare.py` | Compares compiled functions with the original DLL/EXE, byte for byte (exact relocations) |
| `symcheck.py` | Relocation-target check: every call, global and string must point to the same target as in the original |
| `verdict.py` | Build verdicts (MATCH / DIFF / FILED / LIMIT / HUMAN) with the retry budget; writes `Notes\attempts.csv` |
| `scoreall.py <ALL.txt> [Dll]` | One-command scoring of a whole build: unbundles ALL.txt and runs verdict.py per DLL (and SimJP) |
| `triage_lib.py` | Shared helpers for verdict.py and trivial.py (difference categories) |
| `unbundle.py` | Splits `Results\ALL.txt` back into the individual files |
| `varcmp.py` | Scores every experiment variant build (VarA..) separately, per function |
| `build_core.bat` / `build.bat` | The build: compiles `Src\<Dll>\*.cpp` with Intel C++ 5.0.1 in the VM, bundles `Results\ALL.txt` |
| `watch.bat` | VM build watcher: waits for `Tools\queue\request.txt` and runs build_core.bat |

## Free - help with the work

| Tool | What it does |
|---|---|
| `permuter\permute.py <file> <Class::method>` | Background permuter (PC + VM, no AI usage): mechanical rewrites of one function until it matches; report in `Notes\permuter\`; `--list` ranks the real near misses of the last build (bytes differ); for functions a few bytes off, not big differences; `--auto N` works through `Notes\PERMUTER_TARGETS.txt` and then the closest near misses overnight (summary `Notes\permuter\AUTO_<date>.md`) |
| `neighbours.py <Dll> <name or rva>` | Nearest matched neighbours: the already-matched functions whose original code is most like the target's, with their source - read before writing a function (`--show N`, `--top N`, `--all`) |
| `batch.py <folder\file.cpp> ...` | Judges every function of the given files in one table (MATCH / DIFF / size / first difference); `--open`, `--host`, `--results DIR` - for rounds of many small functions; a quick look, not the verdict |
| `next.py` | Which functions to write next: unwritten functions ranked by estimated cost (size, naming evidence, class progress, named callees, closest matched neighbour); `--folder`, `--max-size`, `--json` |
| `mapsuggest.py` | Map entries for references the anti-cheat could not check: re-compares matched functions, takes the original's targets, proposes entries (`Notes\map_suggestions.md`); `--write` adds only those confirmed by two or more functions |
| `inlinecheck.py` | Functions our build calls that the original never calls (usually inline there; in Zoo possibly BBT-pasted) and which non-matching functions they block -> `Notes\inline_candidates.md` |
| `fields.py <Dll> <Class>` | Fields of a class from its methods in the original binary: every offset touched through `this`, with size, reads/writes, a type guess, and a draft `m_unkXX` member list |
| `regress.py --who <header>` / `regress.py <results>` | Shared-header guard: which folders a header reaches, and which functions matched at the last anti-cheat run but no longer do |
| `hostbuild\hostbuild.py` | Compile on the PC without the VM (`--setup`, `--check <folder>` / `--check all`, `<folder>`, `--watch`); results in `Results_host\`, never trusted - for the permuter (`--host`) and quick iteration |
| `notes_index.py <notes.md>` | Index of the notes (`Notes\NOTES_INDEX.md`); `--show <id>` prints one entry, `--find words` searches - read notes through this, not whole |
| `localai\watch_ai.py` | Runs on the PC: a local model (llama-server or Ollama; `localai\start_local_ai.bat` starts model + watcher) reads files named in `Tools\queue\ask_<id>.json` and writes a short answer to `Tools\localai\out\` - saves Claude's usage on long inputs; answers are hints, not evidence |
| `localai\preread.py` | Local-model digests: of `next.py`'s top targets (PREREAD.md, run by `start_local_ai.bat`), of chosen functions (`--va`), and naming evidence for placeholders (`--evidence`, out\ev_*.md); a session asks via `Tools\queue\preread_<id>.txt` |
| `show.py <Dll> <name or rva>` | Everything about one function: tracker/attempts rows, Ghidra's C, annotated disassembly |
| `dis.py` | Annotated disassembly of a whole DLL (objdump + names), split per function |
| `classmap.py` | Classes from vtables in all 19 binaries: base classes, ctors/dtors, slot names (`--slots NAME`) -> `Notes\classes.csv` / `classes.md` |
| `vtables.py <dll>` | Every exported vtable of one DLL with slot names |
| `trivial.py jpog` | The no-judgment work: trivial bodies and identical-code clusters -> `Notes\generated\` |
| `switchgen.py` | Reconstructs a `switch (x) { case K: return CONST; }` function from its jump table |
| `bake.py` | Resolves `#if defined(VAR_X) ... #endif` experiment chains in a source file once a variant wins |
| `inventory.py` | Catalogues a game install folder (file kinds, PE info, hashes) -> `Notes\inventory.csv` |
| `compare_variants.bat` | Compares every experiment variant against the original (PC side) |
| `export_decompiled.bat` / `export_all.bat` | Ghidra headless export of `decompiled\*.c` for one / every binary (run on the PC) |
| `ghidra\ExportDecompiled.java` | Ghidra post-script used by the export scripts |
| `ghidra_path.txt` | Your Ghidra folder (machine-specific - don't publish) |
| `queue\sweep_*.txt` | Flag-sweep definitions for unattended runs in the VM |

## Ideas

Tools worth building when there is time (add yours; remove an idea when it's done or dropped):
- (none yet - add yours)
