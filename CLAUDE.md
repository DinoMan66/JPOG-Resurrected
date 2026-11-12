# CLAUDE: START HERE (JPOG / Toshi matching decompilation)

Read this file first in every session. It replaces re-reading old conversations.
Goal: byte-matching C++ for the 18 code files of Jurassic Park: Operation Genesis (`Original\DLLS\*_inst.dll`,
`Original\SimJP.exe`). Usage limits are the bottleneck, so work in a cheap, scripted way.

## ANTI-CHEAT RULES (read every session; they override anything else in this file)

A function counts only when it is real, readable C++ that the real compiler turns into the original's code.
Checked by the user's independent anti-cheat (`C:\AntiCheat\anticheat.py`, outside your reach) - a
violation fails the whole check, so there is nothing to gain from any of these:

1. **Forbidden in Src\**: inline assembly (`__asm`, `_asm`, `asm`), naked functions, `_emit`, byte arrays
   executed as code, code/data placement pragmas (`code_seg`, `data_seg`, `section`, `init_seg`,
   `alloc_text`), `#pragma comment(linker ...)`, `__declspec(allocate)`, `/alternatename`, hard-coded
   addresses cast to pointers or called (`(T*)0x638148`, `((void(*)())0x401000)()`), `#include` of anything
   that is not a header, and any .obj/.lib/.asm/.bin file. (Functions the original wrote in assembly
   are listed in the ORIGINAL ASSEMBLY section below - ask the user before touching them.)
2. **Compiler flags** (`flags.txt`, `*.cpp.flags`) only from the allowed list: /D /U /I (inside the project or
   C:\stlport), /O.., /G.., /W.., ICC -Q options for code generation. Never /B1 /B2 /Fo /link -Qlocation -Qoption.
3. **Protected tools change only through a proposal** (hash-locked - any direct edit fails the anti-cheat):
   Tools\compare.py, symcheck.py, verdict.py, triage_lib.py, scoreall.py, unbundle.py, varcmp.py,
   build_core.bat, build.bat, watch.bat, Original\*,
   plus every project module they import and any tool added by an accepted proposal.
   To improve one, put the new version in `Tools\proposed\<name>\` with a PROPOSAL.md and ask the user to
   run `anticheat.py <project> trial <name>` (then `accept <name>`) - see "Improving the setup". All other
   tools are free to improve. Never edit files in Results\. Queue commands (Tools\queue\cmd_*.bat) run only while
   the user has enabled them in the VM for a probe session; use them for diagnostics only, never to change or
   replace a compiler, and never to write objects that get scored. The anti-cheat marks such builds as untrusted.
4. **A match needs the right targets.** verdict.py and the anti-cheat check every relocation: the call must go to the same
   function, the load must read the same global, the string must be the same string (Tools\symcheck.py).
   "relocation target differs" is a MISMATCH, never something to explain away.
5. **No justifications.** Comments or notes that argue a difference is acceptable do not change the result -
   a function verifies or it does not. Do not widen tolerances, exclude functions or relabel statuses.
6. **Honest progress.** Report progress only from `Notes\VERIFIED_PROGRESS.md` (written by the anti-cheat).
   Placeholder code (Z_<va>, UIH_<va>, f<va>/m<va>/g_<va>, m_unkXX, pad[], dummy virtuals), compiler-generated
   copies and Microsoft library code are separate tiers and are never reported as reconstruction.
   Prefer giving real names (class, method, member) over generating more placeholders.
7. **Readability standard** (`Notes\READABILITY_STANDARD.md`, calibrated against sm64/oot/mm/tp, enforced by
   the anti-cheat). Hard rules: plain text, consistent formatting (one statement per line), comments on
   non-obvious logic, the game's code written plainly. NOT allowed: types invented for one function and named
   after it (`struct Z_4DA485 { void f(); }`), one-letter methods (`X::f()`), `c0`/`v12` members, generator
   output (never let Tools\gentrivial.py / genshapes.py write into Src\ - analysis output into Notes\ only),
   macros that stamp out function bodies, verification scaffolding (probes, reference units of invented
   globals/classes, files that only force template instantiations).
   ALLOWED as honest placeholders ("decompiled, not fully documented"): offset-named members with an offset
   comment (`/* 0x35C */ bool m_unk35C;`), address-named functions/globals whose purpose is unknown
   (`UIH_4D5A49`, `f48d052`, `g_638068`), unknown vtable slots in a real class (`vf3`). Replace them with real
   names as soon as the purpose is known (renaming members/locals/non-exported names normally keeps every match, but rebuild and re-verify the whole file
   after a rename - on VC6 a spelling can change later functions; recorded names - JPOG exports, strings - are kept
   verbatim). Since 2026-11-10 also NOT allowed: raw offset arithmetic (`*(int*)((char*)this + 0x30)` - declare
   `m_unk30`), steering pragmas / `__forceinline`, redundant constructs added to move the compiler. A macro the
   original evidently had needs an `// original macro: <evidence>` comment. Named functions carry a `// name:`
   source tag (string / vtable / caller / guess). Details: READABILITY_STANDARD.md. Label a deliberate fakematch
   `// FIXME: fakematch`. If a function can only be matched with not-allowed code, do not commit it: add a note
   to `Notes\removed\` and move on. Do not re-add files listed in `Notes\READABILITY_REVIEW.md`; the old
   versions of deleted files are kept (reference only) in `Notes\removed\*.md`.

## Files to know (read only what the task needs)
| File | What |
|---|---|
| `Tools\TOOLS.md` / `Tools\CHANGES.md` | Every tool: free or protected, what it does, how to run it / log of tool changes |
| `Notes\NOTES_INDEX.md` + `Tools\notes_index.py` | **Read this, not MATCHING_NOTES.md**: a short index of every note; print single entries with `--show <id>`, search with `--find words` |
| `Notes\MATCHING_NOTES.md` | Compiler habits + codebase facts (numbered). Too long to load whole - go through the index |
| `Notes\COMPILER_LIMITED.md` | Functions that our ICC build 010525Z cannot match. **Never retry these.** |
| `Notes\function_tracker.csv` | Every exported function of all 19 binaries (18 DLLs + SimJP.exe): dll, rva, size, name, status |
| `Notes\attempts.csv` | Written by verdict.py: attempts per function, category, status |
| `Notes\READABILITY_STANDARD.md` | **What counts as readable source** - every file in Src must meet it |
| `Notes\READABILITY_REVIEW.md` | 2026-10-27 review: files removed / pending your decision; notes in `Notes\removed\` |
| `Notes\VERIFIED_PROGRESS.md` | **The only progress numbers to report** (anti-cheat output, honest tiers) |
| `Notes\classes.csv` / `classes.md` | Tools\classmap.py: 1,024 vtables in all 19 binaries - class, base class, ctors/dtors, every slot's exported name, slots done |
| `Tools\show.py <Dll> <name or rva>` | One function at once: tracker/attempts rows, Ghidra C, annotated disassembly. Use it instead of grepping |
| `Notes\generated\` | From trivial.py: `trivial_<Dll>.cpp`, `clusters.md`, `summary.txt` |
| `decompiled\<Dll>_inst.dll.c` | Ghidra output. Large - grep for the function, never read whole |
| `Results\ALL.txt` | Build bundle (10+ MB). Never read it - feed it to scoreall.py |

## The cheap workflow (do it this way)
0. **Start from a list, not by exploring.** If `Tools\localai\out\PREREAD.md` exists (the user's local model
   pre-read the next targets), stage and read it first: targets in order, each with a short digest. Otherwise
   `python3 -I Tools/next.py` (`--folder TKernelInterface`, `--max-size N`) ranks the unwritten functions cheapest first:
   size, naming evidence, how much of the class already matches, named callees, the closest matched neighbour.
   It is an estimate; the generated lists below stay the first stop for trivial bodies and clusters.
1. **Choose work from `Notes\generated\` first**, before opening Ghidra output:
   - `clusters.md`: "FREE WIN" clusters already have a matched member - copy its source to the others.
     Other clusters: write one function, reuse the shape for the rest.
   - `trivial_<Dll>.cpp`: ready-made bodies for getters/setters/constants/empty functions. Paste into the
     class's .cpp, rename `m_unkXX` to the real member (offset is in the comment).
2. **Batch**: put a whole class or .cpp file into one build round, not one function per round.
3. **Build round** (the user's XP VM runs `Tools\watch.bat`):
   - commit the changed `Src\<Dll>\*.cpp` / `Src\include\*.h`;
   - commit `Tools\queue\request.txt` containing `round-NNN <unix time> <Dll>` (write it from a uniquely named
     local file - the bridge can serve a cached copy of a same-named file);
   - check `Results\DONE.txt` with device_list_dir until its mtime is newer than the request, then stage
     `Results\ALL.txt` only.
4. **Score with one command** and read nothing else:
   `python3 -I Tools/scoreall.py <staged ALL.txt> <Dll>`
   It prints one summary line per DLL, then only functions that changed:
   - `MATCH` done. `DIFF` open, with 2 instructions of context and a category hint.
   - `FILED` / `LIMIT` = compiler-limited. **Stop working on it.** (Exception: the one re-check described under "When a function won't match".)
   - `HUMAN` = source-type difference that survived 4 attempts: ask the user, don't keep trying.
   Categories: encoding, regalloc, sched, shrink-wrap, inline, fp (compiler-limited after 2 attempts);
   stack (reorder local declarations), branch (swap if/else bodies), outlined (missing `inline`?), source.
5. Commit back the updated `Notes\function_tracker.csv`, `Notes\attempts.csv`, `Notes\COMPILER_LIMITED.md`.
6. New habits learned -> one numbered line in `MATCHING_NOTES.md`. Keep it short.
7. End of session: update "Current state" below (numbers + next step). Re-run
   `python3 -I Tools/trivial.py jpog` when many functions changed status.

## ORIGINAL ASSEMBLY (the game itself contains hand-written code here)
- TRenderD3DInterface 0x1002D01D, 0x100317CD, 0x10032445: MMX routines; 0x10038B87: CPU detection (cpuid).
- SimJP.exe: sections `.cms_t`/`.cms_d` (same names SecuROM copy protection uses) and `PSGSFD00`..`PSGSFD_B`
  (unidentified, ~15 KB) are not game code - exclude them.
These are the only places where `__asm` could be legitimate. Ask the user first.

## Code-rules profile (where names come from, what may change bytes)
- Compiler: Intel C++ 5.0.1 (build 010525Z). No RTTI. Every DLL exports its functions by decorated name, so the
  class, function name and parameter types of exported functions are RECORDED: use them verbatim (llvm-undname),
  never rename or "fix" them - that changes the export table. Members, locals and non-exported helpers are free.
- Other evidence: source paths in strings `Z:\Toshi\Source\<Module>\<File>.cpp`, `Z:\Toshi\Plugins\Source\...`,
  `Z:\Projects\SimJP\Source\...` (unit names and folders - keep our Src layout in line with them), `Class::method`
  strings, exported vtables (`??_7`). SimJP.exe also exports its functions by name (13,664 functions + 1,775 data exports).
- Style: Toshi Hungarian-style members (`m_uiMagic`, `m_pChild`, `m_bEnabled`, `m_fScale`), classes prefixed
  `T` (engine), `P` (plugins), `A` (SimJP game). Follow the existing headers.
- Placeholders allowed: `m_unkXX` (offset), `_SlotNN` / `SlotN` vtable slots - name slots from the D3D DLL exports
  (`python3 -I Tools/classmap.py Original/DLLS/D3D/*.dll Original/DLLS/TRenderD3DInterface_inst.dll --slots TSkinShader`: slot N of the HAL class = the placeholder `_SlotN`; e.g. TSkinShader slot 12 = SetSunTheta, 13 = SetSunIntensity).
- `__FILE__` strings must equal the original path: `#line N "Z:\\Toshi\\Source\\TRender\\TFoo.cpp"`.

## When a function won't match: classify the wall first (in this order)
A pinned compiler is deterministic, so a remaining difference means an input differs. Do not call a wall class N
while class N-1 still diverges (adapted from lemiur's wall-identifier):
1. **Referent** - instructions identical, but a call/global/string target differs (symcheck note in verdict.py).
   Fix the identity/label. Never "fix" this with codegen tricks.
2. **Call set** - the set of out-of-line callees differs (verdict categories `inline` / `outlined`). Usually the
   caller's body is incomplete, an inline boundary is wrong, or a helper is open-coded. Finish the caller first.
3. **Control flow** - block/branch/return counts differ (`branch`). A source construct: separate returns vs one
   exit, `while` vs `do`, `||`/`&&` collapse, switch shape.
4. **Register / schedule** (`regalloc`, `sched`, `stack`) - only after 1-3 agree. Check in turn: variable widths
   (`unsigned char` vs `bool`/`int`), one local per meaning, declaration and first-use order, the scope/lifetime
   of temporaries, inline-helper boundaries. Only then is it compiler-limited.
**Helper recovery:** when code reaches into another class's internals, repeats a field path or has a scoped
`{ }` block, the original probably called a small accessor/inline/macro. Restore it in the owning class's header
only with evidence (the same pattern at several sites, an existing helper, a string), apply it at every site, and
rebuild: exact functions must stay exact. This is real source even when no score moves.
**Compiler-limited list:** entries filed before 2026-10-28 only because of regalloc/sched get ONE re-check against
step 4 and helper recovery (one attempt each, note the result in COMPILER_LIMITED.md); after that they are final.
**Fakematches:** if a match needs `volatile`, a dummy local, an empty block, `do{}while(0)`, `+ 0` etc., it is not a
match (MATCH-PENDING in the anti-cheat report). Use the trick as a clue to the real source, then remove it.

## Rules that save usage
- Re-read the ANTI-CHEAT RULES and this section at the start of every build round - rules fade as the
  context fills (momo5502). Keep context small: one file/class per round, fresh session for a new area.
- Routine rounds (trivial bodies, clusters, renames, helper application) run fine on a cheaper model; the
  harness (verdict.py + anti-cheat) is what keeps them honest. Save the strongest model for walls and reviews.
- Retry budget is 2 real attempts per function (verdict.py counts them), each one aimed at the wall class above. Don't hand-craft a 3rd variant of a
  regalloc/sched difference - it is almost always the compiler build (see MATCHING_NOTES #23).
- Flag sweeps run unattended in the VM (Results\sweep*). Read only their log summary, never the outputs.
- Don't read whole dumpbin, ALL.txt, Ghidra files or MATCHING_NOTES.md; grep/slice by function name or
  address, and go through `Notes\NOTES_INDEX.md` for notes. Add new notes as short entries (a finding and
  its evidence, not a diary of rounds).
- Tools need `capstone` (pip) or GNU objdump; trivial.py needs `llvm-undname` (Claude's side) or MSVC `undname`
  for signatures - without it, bodies are still generated with decorated names.

## Mismatch sessions (walls)
A session devoted to functions that are written but do not match. Rules, in this order:
1. Classify the wall first (section above). Most "compiler" differences are source or build inputs.
2. **Budget: 6 build rounds per function per session** for a register / schedule wall, 2 real attempts for
   everything else (verdict.py counts). When it is used up, write the state in `Notes\NOT_MATCHING.md` (what differs, what
   was tried, the best lead) and take the next function. Only the user can extend a budget, per function.
   One function must never consume a session: breadth first, the cheap wins of many functions before the last
   instruction of one.
3. Never commit a steering construct (rule 7). A probe may use one to learn something; `Src\` keeps the plain form.
4. Tools, cheapest first: `Notes\NOT_MATCHING.md` and `COMPILER_LIMITED.md` (what is already known), the header-inline
   and call-site evidence notes (`notes_index.py --show "Header inlines"`), `Tools\varcmp.py` for variants. Our
   compiler build (010525Z) is older than the game's (020125Z): the "inl" family in NOT_MATCHING.md is that
   difference and is not worth rounds. Queue commands and flag sweeps need the user's allow file in the VM.

## Background permuter (no usage)
`Tools\permuter\permute.py <file> <Class::method>` runs on the user's PC: it rewrites one function mechanically
(statement and declaration order, operand order, comparison and increment spellings), builds the copies in a
scratch folder `Src\zzperm\` in the VM and scores them. Use it for functions one or two instructions away at the
register / order level INSTEAD of spending rounds on them:
- **Overnight:** ask the user to run `py Tools\permuter\permute.py --auto 10 --host` (or without --host): it
  works through the 10 closest near misses one by one, drops any that turn out not to be near misses, and writes
  a summary `Notes\permuter\AUTO_<date>.md`. Read the summary first; open a function's report only for EXACT.
- Ask the user to run it (it takes minutes to hours, unattended). Pick the target with `--list`: it ranks the
  last build's functions by bytes that differ. Only near misses (a few bytes, same size) are worth a run; a
  function tens of bytes off needs a source change by hand, not permutations (it warns at the start).
- Its report is `Notes\permuter\<file>__<function>.md`. An EXACT result is a candidate: apply the diff to the real
  file yourself, build and verify normally, and check the change reads like something a programmer would write.
- While `Tools\queue\permuter.lock` exists do not queue builds, and never touch `Src\zzperm\`.
- With `--host` it builds on the PC through `Tools\hostbuild` (seconds per round, `Results\` untouched).

## Helpers for writing and changing code
- **Before writing a function:** `python3 -I Tools/neighbours.py <Dll> <name or rva>` lists already-matched functions whose original code
  is most like it, with their source (`--show 2` for more). Copy how they are written (idioms, types, order), not
  their names - a neighbour is a model to follow, not evidence for a name.
- **Rounds with many small functions:** `python3 -I Tools/batch.py <folder/file.cpp> ... --results "<staged results>"`
  gives one line per function instead of reading verdict output function by function. It is a quick look: the
  verdict that counts is still verdict.py plus the anti-cheat.
- **Before writing or extending a class header:** `python3 -I Tools/fields.py <Dll> <Class>` lists every
  offset the class's methods touch through `this` (size, reads, writes, a type guess, which methods) and drafts
  the `m_unkXX` member list. It is evidence to check against the code, not a layout to paste.
- **After changing a shared header:** `python3 -I Tools/regress.py --who <header.h>` names the folders to rebuild;
  after that build, `python3 -I Tools/regress.py "<staged results>"` lists functions that matched at the last
  anti-cheat run and no longer do. A header change stays only when it reports no regressions.
- **Host builds** (`Tools\hostbuild`, when the user has set it up): a Claude session may ask for one with
  `Tools\queue\hostreq_<id>.txt` (`<id> <unix time> <folder>`) and read `Results_host\`. They are for quick
  iteration only: nothing counts until a normal VM build and the anti-cheat verify it, and progress is never
  reported from `Results_host\`.

## Local model (reads for you)
When `Tools\localai\watch_ai.py` is running on the user's PC, a small local model can read project files and
report back, so the text never enters your context:
- Commit `Tools\queue\ask_<id>.json` (`{"id", "question", "files": ["Notes/X.md", "decompiled/zoo.exe.c:100-400"],
  "grep": "regex", "around": 12, "max_words": 250}`), wait for `Tools\localai\out\<id>.md`, stage and read it.
- Worth it only for input over about 20 KB: long notes, build logs, a large Ghidra function, "which of these files
  mention X". For anything smaller, or anything `notes_index.py` / grep answers, read it yourself.
- The answer is a hint from a small model. It can be wrong or incomplete. Never use it as evidence for a name, a
  rule or a match, never paste its text into `Src\` or the notes; open the lines it cites before acting on them.
- If no answer appears within a few minutes the watcher is not running: carry on without it, don't wait.
- **Pre-reading:** `start_local_ai.bat` also runs `Tools\localai\preread.py`, which asks the model for digests of
  `next.py`'s top targets (what the function does, fields, callees, strings) into `Tools\localai\out\pre_*.md`,
  listed in `PREREAD.md`. Same rule: a digest saves reading; names, types and layouts still need their evidence.

## Unverified references (map entries)
When VERIFIED_PROGRESS.md reports matched functions with unverified references, run
`python3 -I Tools/mapsuggest.py` (staged Results with `--results`): it re-compares those functions and lists the
original's target for each reference whose address is unknown (`Notes\map_suggestions.md`). Only CONFIRMED
entries (two or more matched functions, all pointing to the same address) go into the maps (`--write` adds them);
a single reference is not evidence. This raises how much the anti-cheat checks, not the match count.

## End of every session
1. Update "Current state" below (numbers from verdict/scoreall only, last build round, next step) and the notes.
2. Re-run `python3 -I Tools/notes_index.py Notes/MATCHING_NOTES.md` if notes were added, and commit `Notes\NOTES_INDEX.md`.
3. Update `README.md` in the project folder when something a visitor should know has changed: what is covered,
   new tools, how to build, the layout. Do NOT touch the block between `<!-- status:start -->` and
   `<!-- status:end -->` - the anti-cheat rewrites it with verified numbers.
4. Tell the user to run the anti-cheat. It also adds a row to `Notes\SESSIONS.csv` (readable change, verdicts,
   permuter/local-model/host-build use since the last run): read it when judging which helpers pay off; never edit it.
   On a CLEAN run it refreshes the README status and rebuilds the
   `public repository` folder (the files meant for GitHub; nothing copyrighted or personal is copied). Never write
   into `public repository` yourself, and never put game files, third-party files or anything about the user's PC
   into `Src\`, `Tools\` or `Notes\` - those folders are published.

## Improving the setup (the tools are meant to grow)
When the same manual step comes up a third time, a check misses a kind of problem, or a tool's output wastes
reading, improve the tool or write a new one. That is real progress, not a detour. Two kinds of tools:

| | Free tools | Protected tools (rule 3) |
|---|---|---|
| What | everything that helps: analysis, search, ranking, drafting, reports (show, classmap, trivial, ...) and every new helper | what decides whether a function counts: comparison, relocation check, verdicts, build scripts |
| How to change | edit or create directly, in any session | proposal in `Tools\proposed\<name>\`, the user runs trial + accept |

**Free tools** - keep them honest and findable:
- A docstring at the top: purpose, usage, inputs, outputs. One line in `Tools\TOOLS.md`; each change one line in
  `Tools\CHANGES.md` (date, tool, what and why).
- Output goes to the screen or `Notes\` - never into `Src\` (rule 7), `Results\`, `VERIFIED_PROGRESS.md` or
  `verified_functions.csv`. A free tool may suggest (rank candidates, draft code you then write by hand, flag
  problems); whether a function matches is only ever decided by verdict.py / scoreall.py and the anti-cheat.
- Protected tools must not import a free module (the anti-cheat would then lock it too). Share code by copying
  it into the protected tool through a proposal, or keep it in the free tool.
- Try a changed tool on real data (the last build, a known function) before relying on it. Delete experiments you
  don't keep (list them for the user - you can't delete files on the PC).

**Protected tools** - a proposal is one folder `Tools\proposed\<short-name>\`:
- The changed or new file(s) laid out as under `Tools\` (`compare.py`, `build_core.bat`, ...). Changes to free
  tools never go here.
- `PROPOSAL.md`: first line a one-line title, then *What* changes, *Why* (the problem, with function names and
  addresses), *Expected effect* (stricter / looser / neutral, and which functions should change verdict) and
  *Tested* (score the current build with the old and the new version on your side and list the differences).
- **Stricter** (catches wrong targets, adds a check) is welcome. **Looser** is allowed only when it models
  something the real toolchain does, with evidence from the original binary (e.g. the post-link optimizer
  pasting tiny calls into callers); every newly accepted function must be explained. Never loosen a check to get
  a stuck function through - that is the wall-classification job, not the tool's.
- Build-script changes can't be tested by the trial (the build runs in the VM): say how to test them.
- One change per proposal, small enough to read. Not proposable: `Original\`, `Tools\lib\`, the queue, and the
  anti-cheat itself (it belongs to the user - suggest improvements in words).
- The user runs `trial`: it shows them the diff, re-verifies every function with both versions and writes
  `TRIAL.md` into the proposal folder (newly accepted / newly rejected functions). Read it; fix the proposal if
  the result is not what PROPOSAL.md predicted. After `accept` the proposal moves to `Tools\proposed\accepted\`
  and `Tools\CHANGES.md` records it. Update this file if the workflow changes.

Ideas you can't do now go to the "Ideas" list at the end of `Tools\TOOLS.md`.

## Current state (2026-10-29, TGuiInterface session, rounds 192-225)
- **2026-11-10 (setup update).** TGFXFileInstanceObject.cpp: the shader accessors used raw offsets
  (`*(int*)((char*)this + 0x30)`), now declared members of TGFXInstanceShaderI (m_iTextureStagesState 0x30,
  m_unk34, m_fAlpha 0x38) - round-258 (TRenderInterface) was queued to confirm that Render still matches; check its
  result first. New rules: raw offset arithmetic, steering pragmas, `original macro:` evidence for boilerplate
  macros (the CreateObject / CreateObjectInPlace family is a candidate), notes through Notes\NOTES_INDEX.md,
  wall budget (section "Mismatch sessions"). Last build round: round-258.
- **Mismatch clean-up, rounds 228-242 (all DLLs).** scoreall (full build round-241): TKernelInterface 977 -> 1004 matched
  (24 open, 57 compiler-limited), TGuiInterface 490 -> 504, TRenderInterface 923, PPropertyParser 201, TInputInterface 90,
  TInputDXInterface 97, TApplication 20; no regressions. scoreall numbers only until the anti-cheat is re-run. Main levers:
  missing header inlines found from call-site evidence (MATCHING_NOTES "Header inlines and call-site evidence"), TU splits
  (TKernelDebugFile.cpp, TGUIEffectManagerCreate.cpp, TVectorCalls.cpp), struct sizes (ISO9660Directory/File), TMemory's two
  TNodeList<MemBlockSlot> lists, and source bugs (TGUIWidget::AllowsFocus returns 0). Most of what is left is register
  allocation, scheduling, block layout or x87 constant size (see COMPILER_LIMITED.md); the rest are unwritten bodies (the GUI
  InitialiseStatic/DeinitialiseStatic property-set code, TGUIWindow/TGUILayoutInfo/TGUIWidgetInfo ctors and dtors).
  Anti-cheat 2026-10-29 21:55: 2,433 verified (readable), 285 mismatches, 0 wrong targets; its one hard-rule violation
  (packed statements in TRandom.cpp) is fixed. Last build round: round-246.
- **Mismatch clean-up, round 226 (TKernelInterface):** the 4 wrong-target string operator+ (anti-cheat 2026-10-29 13:26) fixed by
  moving every by-value TCString/TWString function into TCStringCtors.cpp (MATCHING_NOTES "round 226"). scoreall: 886 -> 900 matched,
  0 regressions; anti-cheat 14:22: 2,339 verified, 0 wrong targets. Round 227: TCString::Mid MATCH (901). Last build round: round-227.
- **TGuiInterface.dll (rounds 192-225, written from scratch).** scoreall at round 225: 490 matched, 47 open differences,
  7 compiler-limited, 0 need a human, 613 not written yet (22 matched at round 192). scoreall numbers only: the anti-cheat has NOT
  been re-run, VERIFIED_PROGRESS.md is stale. Same session: TKernelInterface 876 -> 888, PPropertyParser 201 -> 203.
- Sources in `Src\TGuiInterface\` (flags.txt empty), one header per class in `Src\include\`: TGUIFunction family, TGUIAudioContext,
  TGUIMemory, TGUIComponentInfo, TGUIRectangle/Alignment/Colour/Point, TGUIDisplayContext, TGUIStateRule/StyleState/StyleRootComponent,
  TGUILayoutInfo/PropertySpec, TGUIDeserialisable, TGUIElement, the five TGUI*Component classes (+ TGUIComponentConstructors.cpp: the
  default constructors live in their own file on purpose, see MATCHING_NOTES "TU-split rule"), the seven PPropertyBlock-derived
  TGUI*Block classes, TGUIWidget, TGUIWindow, TGUIStyle, TGUIWidgetInfo, TGUILayoutManager, TGUITextureSection/FontGlyph/TextureAnimation.
  Details: MATCHING_NOTES.md "TGuiInterface (rounds 192-208 ...)".
- Last build round: round-225. Open / retry candidates (all 2/2 or compiler-limited unless noted): TGUIWidget::AllowsFocus (source: the
  no-parent path returns 0, 2/2 used), GetInteriorWidth/Height (2/2), TGUIElement ctor, TGUIDeserialisable::ValidatePropertyInfo,
  TGUIIconComponent factories, TGUIHorizontalTripletComponent::GetPreferredSize, TGUIPropertySpec::IsEnumerated; the empty
  InitialiseStatic/DeinitialiseStatic stubs in the new classes are placeholders (the originals build the property sets).
- Not written yet / entangled: TGUIScreen (second vtable, 74 todo), TGUIInterface (72), TGUIFont (needs a hash table), TGUIWidgetAction
  (TDList/TFreeList/TGenericEmitter), TGUIActionMap, TGUIInputContext, TSortedArray<T, Comparator> (needed by every
  GetPropertyInfoOrderedSet = vf12), TGUIStateVarInfo, the `ms_oPropertySetOrdered` statics, all constructors/destructors of the new
  classes, Deserialise/Serialise bodies and the property Val_/Get_/Set_ functions that use other types.
- Next step: TSortedArray + the vf12/ordered-set statics (unlocks ~10 small functions per class), then the constructors of the
  classes written here, TGUIScreen accessors, then PGUICore.dll (823 functions).

### Earlier state (2026-10-29, TKernelInterface sessions, rounds 090-188)
- **TKernelInterface.dll (rounds 090-188).** scoreall at round 188: 876 matched, 115 open differences, 66 compiler-limited,
  1 need a human (TCString::Mid, attempt 4/2), 569 not written yet. These are scoreall numbers; the anti-cheat has NOT
  been re-run since, so VERIFIED_PROGRESS.md is stale. Run `C:\AntiCheat\anticheat.py` before quoting any number as verified.
  Session notes: MATCHING_NOTES.md "rounds 123-178" and "rounds 180-188".
- Sources in `Src\TKernelInterface\` (flags.txt empty on purpose, no `-Qsfalign`): TAABox, TPlane, TSphere,
  TVector2/3/4, TQuaternion, TMatrix44, TMath (+TMathData.cpp for the exported PI), TRandom, TSystem, TCString
  (TCString + TWString), TBitArray, TDList, TNodeList, TNTree, TPool, TFreeList, TKernelFiles (TFile family),
  TKernelClass (TClass), TKernelSystem (ISO9660 structs, TKernelInterface and TScheduler accessors).
  Kernel-internal headers: TKernelMisc.h, TKernelContainers.h, TGenericLists.h, TKernelFiles.h, TKernelClass.h,
  TKernelSystem.h. Details and the matching tricks are in MATCHING_NOTES.md ("TKernelInterface rounds 093-122").
- Open / filed lists and wall classes are in COMPILER_LIMITED.md and scoreall output (regalloc, shrink-wrap,
  sched, fp, branch). Retry candidates with 1/2 attempts left: TVector2::IsNormalised, TVector3::IsReasonable,
  SetUnitVectorProjection, SetVectorProjection, TMath::LineSegmentVsLine2D, ISO9660 operator=, TISOFileSystem ctor.
- Not written yet: TMemory (nested MemNode/MemBlock), TObject-based classes (TTask, TTimer, TScheduler body,
  TKernelInterface body), TLocale, TFileLexerUTF8/UTF16, string operator+ (needs an inline TCString ctor),
  x87 TMath functions (Sin/Cos/Tan/ATan2/SinCos/Pow/Log/Exp: probably need `__asm`, a user decision),
  the Ceil/Floor/Round family, TFileSystem Create/Open.
- Next step: TObject-style layout for TKernelInterface/TScheduler/TTask, TMemory, then more TKernelInterface
  FREE WIN clusters; after that TGuiInterface.dll (1157 functions, no Src dir yet) or PGUICore.dll (823).

### Earlier state (2026-10-27)
- **Mismatch clean-up (2026-10-28, rounds 85-88):** fixed the wrong-target match (PutPropertyUnique) and 7 more:
  TQList::InsertTail through the node, iterator comparisons by value, `End()` cached in GetMaterial/GetProperty
  (MATCHING_NOTES, last 5 lines). PPropertyParser 201, TRenderInterface 923 matched; no regressions. Leftover
  experiment chains (VAR_*, TML_POS, TKF_FORM) resolved to their active branch. Tracker statuses caught up
  (297 earlier matches were still 'todo'). Open: TQLIST_FORM (two forms of TQList.h in different files); ICC
  branch-layout differences don't follow the source spelling (don't spend attempts swapping if/else).
  Remaining differences: PPropertyParser 44, TRenderInterface 60 open + 50 compiler-limited, TInput 9 + 4.
  Last build round: round-088.
- **SimJP.exe added to the tracker (2026-10-28, user's decision - keep the numbers honest):** Notes\function_tracker.csv
  now has 20,432 functions = 6,768 in the 18 DLLs + 13,664 in SimJP.exe (rows `SimJP.exe`; its 1,775 data exports
  are not functions and are left out). Still to do: 19,298. trivial.py (re-run, Notes\generated\): 4,677 trivial
  bodies, 815 identical-code clusters (52 FREE WIN) covering another 2,602, about 12,000 need real work.
  The tracker lists exported functions only, in every binary: unexported statics/library code are not counted.
  SimJP.exe source goes in `Src\SimJP\` (build request folder name `SimJP`; not built yet, so the first round may need build fixes). Tools\scoreall.py scores SimJP builds
  (change applied 2026-10-28).
- Readability review (2026-10-27, calibrated standard): 106 files readable, 6 "decompiled, not fully documented"
  (TInputInterface.h m_unk04/m_unk10/m_unk34, TFileLexer.h m_pad04/m_pad09, TKernelInterface.h Slot0,
  TMaterialLibrary/TGFXFileInstanceObject _SlotNN - names recoverable from the D3D DLL exports). Only the 5 old
  copies in Src\*.cpp (root) are deleted. Documentation to-do: Notes\READABILITY_REVIEW.md.
- Anti-cheat run 2026-10-27: 917 TRenderInterface functions verified, all readable (real names), 0 wrong
  relocation targets, 0 rule violations. The other DLLs were not in the last build - re-verify with --rebuild.
- verdict.py now tolerates only real relocations (exact .rel data) and checks every relocation target.

### Earlier state (2026-10-21)
- TRenderInterface: 917/1048 exported functions matched, 65 open differences (mostly regalloc/shrink-wrap: they
  will be auto-filed on their next changed attempt), 45 known compiler-limited, 21 not written yet.
- TApplication 16/16 and TInputInterface 74 matched earlier; PPropertyParser partly written (rounds 13-26).
- Whole project: 5,634 functions still to do. trivial.py: 1,267 trivial (C++ generated), 371 identical-code
  clusters cover another 1,024 (37 FREE WIN clusters, e.g. 99x `CreateObjectInPlace` = copy from
  TCameraObject). About 3,300 need real work.
- Next steps: (1) the 21 unwritten TRenderInterface functions; (2) FREE WIN clusters in clusters.md;
  (3) paste trivial functions DLL by DLL, starting with the DLL you work on next.
- Last build round: round-084.
