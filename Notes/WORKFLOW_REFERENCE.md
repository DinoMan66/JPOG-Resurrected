# Workflow reference

Sections moved out of CLAUDE.md on 2026-11-12 to keep it short. The text is unchanged and binding;
CLAUDE.md's "Reference sections" summarises the rules in them.

## Mismatch sessions (walls)
A session devoted to functions that are written but do not match. Rules, in this order:
1. Classify the wall first (CLAUDE.md, "When a function won't match"). Most "compiler" differences are source or build inputs.
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
- **Choose its targets yourself:** whenever you park a near miss (at most 24 bytes differ in batch.py), add a line
  `<folder\file.cpp> <Class::method>` to `Notes\PERMUTER_TARGETS.txt` (commit it). `--auto` runs the closest of them
  first, skips those further off without a build (listed in the summary), keeps the rest queued for the next run,
  then fills up from the last build.
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
- **Missing inlines:** `python3 -I Tools/inlinecheck.py` (`--results` for a staged build) lists functions our build calls
  that the original never calls, with our callers that do not match yet (`Notes\inline_candidates.md`).
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

## Unverified references (map entries)
When VERIFIED_PROGRESS.md reports matched functions with unverified references, run
`python3 -I Tools/mapsuggest.py` (staged Results with `--results`): it re-compares those functions and lists the
original's target for each reference whose address is unknown (`Notes\map_suggestions.md`). Only CONFIRMED
entries (two or more matched functions, all pointing to the same address) go into the maps (`--write` adds them);
a single reference is not evidence. This raises how much the anti-cheat checks, not the match count.

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

