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
| `Notes\FOR_OPUS.md` | Hard functions handed off by Sonnet sessions; the starting list of Opus sessions |
| `Notes\WORKFLOW_REFERENCE.md` | Mismatch sessions, permuter, helpers, map entries, improving the setup (full text) |
| `Notes\HISTORY.md` | Older "Current state" entries |
| `Notes\FROM_ZOO.md` | Leads from the Zoo Tycoon project to test here: read before parking a wall or filing compiler-limited |
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
   **Breadth across DLLs:** take the list without `--folder`, so the cheapest functions of every DLL compete. When a
   DLL's remaining targets mostly need missing pieces (undeclared vtable slots, unknown members, headers that do not
   exist yet), stop there: put that structural work in `Notes\FOR_OPUS.md` as one line per class and move to the DLL
   with the next cheapest functions.
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
5. Commit back the updated `Notes\function_tracker.csv`, `Notes\attempts.csv` and `Notes\COMPILER_LIMITED.md`
   **after every scored round** (verdict.py writes them on your side; the wall budget and Notes\SESSIONS.csv read them on the PC).
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
Before parking anything: run `python3 -I Tools/inlinecheck.py` (a callee the original never calls is usually an
inline there) and check `Notes\FROM_ZOO.md` (what the other project learned about the same kind of wall).
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

## Reference sections - read `Notes\WORKFLOW_REFERENCE.md` when the task needs them
These moved out of this file to keep it short; the full text there is unchanged and still binding. The rules in them:
- **Mismatch sessions (walls):** classify the wall first; budget 6 build rounds per function per session for a
  register / schedule wall, 2 real attempts for everything else, then write it up in `Notes\OPEN_WALLS.md` and move on
  (only the user extends a budget). One function must never consume a session. Never commit a steering construct.
  Probe sessions need the user (`C:\anticheat_allow_cmd.txt` in the VM): ask first, say which probe and why.
- **Background permuter:** add each parked near miss (at most 24 bytes differ in batch.py) to `Notes\PERMUTER_TARGETS.txt`;
  functions further off need a source change, not permutations. The user runs
  `py Tools\permuter\permute.py --auto 10 --host`. An EXACT result is a candidate: apply it by hand, build, verify.
  While `Tools\queue\permuter.lock` exists do not queue builds; never touch `Src\zzperm\`.
- **Helpers:** `neighbours.py <Dll> <name>` before writing a function (a model to follow, not evidence for a name);
  `fields.py <Dll> <Class>` before a class header (evidence, not a layout to paste); `batch.py` for a quick table (not the
  verdict); `regress.py --who <header.h>` after a shared header change - the change stays only with no regressions;
  `inlinecheck.py` for missing inlines. Host builds (`Tools\queue\hostreq_<id>.txt`, `Results_host\`) are for quick
  iteration only: nothing counts and nothing is reported from them.
- **Map entries:** `mapsuggest.py`; only CONFIRMED entries (two or more matched functions agree) go into the maps.
- **Improving the setup:** free tools are edited directly, with a line in `Tools\TOOLS.md` and `Tools\CHANGES.md`, and
  never write into `Src\`, `Results\`, VERIFIED_PROGRESS.md or verified_functions.csv. Protected tools change only
  through `Tools\proposed\<name>\` with a PROPOSAL.md; the user runs trial and accept. Never loosen a check to get a
  function through.

## Local model (reads for you) - use it every session
When `Tools\localai\watch_ai.py` runs on the user's PC (`start_local_ai.bat`), a local model reads project files
on the PC and writes short answers, so the text never enters your context. Reading is your largest cost; hand
the model every job below instead of reading the input yourself:
- **Rule - check before you read.** Before reading any input over about 8 KB yourself (a Ghidra function, notes,
  a log, a `Notes\removed\` source note), stage `Tools\localai\out\` and use the digest if there is one. If there is
  none, queue one (`preread_<id>.txt` with `--va ...`, or an `ask_<id>.json`) and work on something else until it
  arrives. Read the input yourself only when the digest is not enough, and then only the lines it cites.
- **Automatic:** every build request you queue makes the watcher pre-read that folder's next 12 unwritten
  functions. Stage `Tools\localai\out\PREREAD.md` after every scored round and take the next batch from it.
- **Naming evidence (documentation rounds):** commit `Tools\queue\preread_<id>.txt` containing
  `--evidence TGuiInterface:0x73e0 TGuiInterface:0x7420` (any number of functions). For each it collects every caller's use, the strings
  and callees, and at most two name candidates with the lines behind them -> `Tools\localai\out\ev_<id>.md`.
- **Digests of the batch you chose:** `Tools\queue\preread_<id>.txt` with `--va TKernelInterface:0x141c0 ...` (or
  `--folder <x> --top 20`) -> `Tools\localai\out\pre_<id>.md`. PREREAD.md only covers next.py's own list.
- **Questions about any large file:** `Tools\queue\ask_<id>.json` (`{"id", "question", "files":
  ["decompiled/TKernelInterface_inst.dll.c:100-400", "Notes/OPEN_WALLS.md"], "grep": "regex", "around": 12, "max_words": 250}`), e.g.
  "which functions call FUN_x and with which arguments" over the whole Ghidra file (with `grep`), the long notes
  in `Notes\removed\*.md`, build logs, MATCHING_NOTES entries beyond what NOTES_INDEX.md says.
- **Never wait for it.** Queue all requests for the next batch at the start of a build round, then build; read
  the answers (stage `Tools\localai\out\`) when the round is scored. A digest arrives in about a minute.
- Answers are hints from a small model: never evidence for a name, a rule or a match, never pasted into `Src\`
  or the notes. Open the lines they cite (file and line numbers) and use what those lines show.
- If nothing appears within a few minutes the watcher is not running: carry on without it.

## No shell in the session? Ask the PC to run the tool
Some sessions can stage and commit files but cannot run commands. Then every `python3 -I Tools/<tool>.py ...` in
this file is run by the user's watcher instead: commit `Tools\queue\run_<id>.txt` holding the command on one line
(e.g. `next.py --top 30 --max-size 400`, `batch.py gx\gxcanvas.cpp --results Results`, `verdict.py ...`), then stage
`Tools\localai\out\run_<id>.txt` (usually ready within seconds; verdict runs take longer).
**Batch them:** one file may hold up to 40 commands, one per line (e.g. a `show.py` line for every function of the
batch); the outputs come back together in one file. One commit and one read instead of forty. It runs on the PC's
own files, so verdict.py's Notes\attempts.csv is updated there directly and needs no commit back. Only the
project's own tools run, from the project folder; paths must stay inside the project. If no answer appears within
a few minutes, the watcher is not running: ask the user to start `Tools\localai\start_local_ai.bat`.

## Documentation rounds (placeholders -> readable)
Matches with honest placeholder names (`vslotNN`, `f<va>`, `m_unkXX`) count as "decompiled, not documented", not
as readable. Each session, before writing new functions, spend one round promoting them: queue `--evidence` for
the placeholders in VERIFIED_PROGRESS.md's per-file list, rename those whose evidence holds (name tag as in rule
7, `// name: caller|string|vtable (confidence)`), rebuild the file and re-verify it. A rename never changes the
code, so it is the cheapest readable gain there is; leave a placeholder alone when the evidence is thin.

## Hand-off to Opus (`Notes\FOR_OPUS.md`)
Sonnet sessions do breadth: many functions, each cheap. A function that is clearly hard goes to `Notes\FOR_OPUS.md`
WITHOUT an attempt, so no budget is spent on it. Hand off when any of these holds:
- original size over 400 bytes (the `size` column of next.py; Sonnet sessions use `next.py --max-size 400`);
- heavy x87 floating point, or STLport / template-heavy code (several inlined container or string calls);
- the function belongs to a family that already has an open wall (OPEN_WALLS.md, NOT_MATCHING.md, COMPILER_LIMITED.md);
- it needs one of the judgement leads in `Notes\FROM_ZOO.md` (inline budget, definition order, out-of-line helpers).
Also hand off every function you park after using its budget, with what you tried. One line each, format at the top
of the file. Opus sessions (their prompt says so) work FOR_OPUS.md top to bottom under the same rules and budgets,
then `next.py --min-size 400`. Never hand off to avoid a cheap function, and never delete someone else's open line.

## End of every session
0. Check before you stop: `Notes\attempts.csv` committed after the last scored round; `Notes\PERMUTER_TARGETS.txt`
   lists this session's near misses; `Notes\FOR_OPUS.md` has a line for every function you handed off or parked; the placeholders you could not name are still placeholders, not guesses.
1. Update "Current state" below (keep the three newest entries, move older ones to `Notes\HISTORY.md`; numbers from verdict/scoreall only, last build round, next step) and the notes.
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

## Current state (newest sessions; older entries in Notes\HISTORY.md)
- **2026-11-14 (TRenderD3DInterface, rounds 530-568, largest-first session).** scoreall: TRenderD3DInterface 144 -> 227 matched (13 open, 2 compiler-limited, 68 not written); regress rebuilds after the shared-header changes (TObject.h, TMath.h, TModel.h, TTextureResource.h): TRenderInterface 923 / TGuiInterface 716 / PGUICore 475 / PPropertyParser 206 / TInputDXInterface 92 / TInputInterface 85, all unchanged. Levers: gamma/colour helpers (TMath::Clip/Gain, GetHALMemInfo), index/vertex pool and block resources, TModelD3D (TModel slots renamed to the exported Create/Delete/Load/Unload/LoadTMDHAL; inline IsLoaded in TModel.h), the SAFE_RELEASE macro (original double null test, in d3d8min.h with the evidence comment), CreateModel, DestroyDisplay/AdjustDisplay, FailedD3D/FailedDisplay message boxes (strings read from the original), accelerator table, SetTextureAddressMode/SetDefaultRenderStates (new D3D enums), TTextureFactoryHAL::CreateTextureFromFile (friend + overload slot order: ICC gives overloaded virtuals their slots in reverse declaration order). Open/parked (in PERMUTER_TARGETS.txt and FOR_OPUS.md): IsTextureFormatSupported, Supports32BitTextures (filed), TMSWindow::Destroy and CreateAcceleratorTableA (the original does not inline the small callees), TVertexBlockResource::DestroyHAL, DestroyAdapterDatabase, TIndexBlockResource copy ctor. Handed to Opus: 7 lines. Placeholders renamed: m_iUnk10 -> m_hInstance (TMSWindow). Anti-cheat NOT re-run. Last build round: round-568. Next step: TRenderD3DInterface emitter/TWString/TD3DAdapter headers (BeginScene/EndScene/Update/Create/Destroy), HALBuffer structs, then the smaller DLLs without a Src dir (TRenderD3DInterface is the largest DLL already started; continue with the next unstarted DLL).
- **2026-11-13 (PGUICore + TGuiInterface, rounds 468-516, evening session).** scoreall: PGUICore 456 -> 475 matched (59 open, 15 compiler-limited, 274 not written; PGUIDialog::OnButtonPress now matches, TGUIScreen::GetPointerPositionX/Y moved inline into the header); TGuiInterface 689 -> 716 (49 open, 26 compiler-limited, 368 not written; new minimal TGUIInputContext.h/.cpp with SetScreen, TGUIScreen::SetInputContext, TGUIScreen::OnButtonRelease; FindLayoutClass/FindComponentClass filed 2/2). Levers: GetStaticWidgetInfo/ms_widget_info on the 11 PGUICore widgets, TGUIInterface class-list statics (Add*/Get*ClassList), TGUIFont::SetScale, TGUIScreen accessors and members (+0xF8..+0x140), Clone for ListBox/MenuDialog/MenuBar/SliderBar/TableBox (MenuBar/SliderBar/TableBox needed trailing member placeholders m_unkAC/m_unkB4/m_unkDC to get the object size right; the TableBox member layout before +0xDC does not match its constructor and needs a rework). Open: Find*Class loops and FindFont/DeleteAllSkus (shrink-wrap/regalloc), TNodeList InsertTail family, dtor 'set vtable then call base' wall. Handed to Opus: 6 lines in FOR_OPUS.md. No placeholders renamed. Anti-cheat NOT re-run. Last build round: round-516. Next step: fix the PGUITableBox member layout against its ctor (0x18d90: emitters at +0x8C/+0x98, list at +0xA4), TGUIInputManager slots, then the smaller DLLs (no Src dir yet).
- **2026-11-13 (PGUICore, session 07:14-09:09 UTC, rounds up to 467).** scoreall: PGUICore 433 matched (62 open differences, 14 compiler-limited,
  314 not written yet; the last full figure of the previous list was 399 at round 436). Anti-cheat NOT re-run: scoreall numbers only. New/extended
  sources: PGUIMenuDialog/MenuBar/MenuTree (FindItemData, GetItemAtIndex, OnButtonRepeat, AddMenus/RemoveMenus, InvokeMenu(int,int,int)),
  PGUIMenuTreeItem (RemoveItem, ChooseChildItem, ChooseNextItem, FindChildItem), PGUIListBox (NotifyFocusLost, OnButtonRepeat, FindItemWidget,
  FindWidgetItem, GetFirstItemWidget, Deserialise, DeleteItemList; new TU PGUIListBoxStyles.cpp for the style properties), PGUITableBox
  (OnButtonRepeat, IsItemVisible), PGUIButton/PGUILayoutManager abstract factories, DiscLayout Val_offsetangle, TableBox Initialise/InsertStampWidgets, MenuTreeItemStyle::GetParameterCount, OverlayLayout::SetForceSameWidth, GridLayout::SetNumRows. Open walls (2/2 or 1/2, in
  PERMUTER_TARGETS.txt): TNodeList::InsertTail hoisted-lea family (ListBox/TableBox AddItemImpl, MenuTreeItem::AddItem, DiscardButton x2,
  DiscardDialog), callee-saved rotation (RemoveAllItemsImpl x2, SizeToFit, EnsureVisibleImpl x2), Val_ regalloc, PropagateState (stack frame).
  Not written: functions that need TGUIWidget slots 34+ (slot 33 = Pack, 34 = Layout(-1,-1)), TGUIScreen members (+0x114/+0x118, +0xCC stack),
  emitters (Throw), TMath::PI (kernel-internal header only), the TGUIInterface FindStyleInstance declaration. Last build round: round-467.
  Next step: declare TGUIWidget slots 34-41 in TGUIWidget.h (check that TGuiInterface's vtable still links), then Layout/Paint/UpdateSelection
  families; then PGUICore ctors/dtors and InitialiseStatic/DeinitialiseStatic; then the next smaller DLL (TRenderD3DInterface).
