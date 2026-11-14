# Lessons from the Zoo Tycoon project (for JPOG)

Zoo Tycoon is the other matching decompilation in this setup (Visual C++ 6.0 SP3 plus the BBT post-link optimizer).
Its compiler is different, so nothing here is a rule for ICC: each item is a lead to TEST here, with the Zoo note it
comes from (ZooTycoonDecompiled\Notes\MATCHING_NOTES.md). Read this before filing a function as compiler-limited and
at the start of every mismatch session. Add a JPOG note when a lead is confirmed or refuted here.

## Leads for the open groups in NOT_MATCHING.md

1. **"inl" group (about 25 functions): test an inline budget before blaming the compiler build.** In Zoo, whether
   the compiler inlined a small helper depended on how much OTHER inline work the calling function had: with too
   little inline work in our source, our build inlined helpers that the original called out of line. Adding the
   original's real inline calls (accessors written as plain member reads in our source) made the helpers stay calls
   and the functions matched (Zoo 66; UIEditableText, UIGraph). ICC also inlines within a size budget per caller.
   Test on one "inl" function: compare its size and call list with the original, write every member access the
   original does through an accessor as that accessor, and try throw-away variants with one more inline call.
   JPOG's own rule belongs next to it: a callee defined AFTER its caller in the file is not inlined into an exported
   inline copy ("Header inlines and call-site evidence") - definition order is a second lever.
2. **"regalloc" where the original reloads a member it has just tested:** a call sat in between - usually a tiny
   out-of-line getter (Zoo 63: DX8Sound::play reloaded mBuffer; writing the getter call matched four functions that
   had been filed as final).
3. **"regalloc" with a value held in a callee-saved register across a call:** a LOCAL copy of the member
   (`T* o = m_owner;`) keeps it in a callee-saved register; an inline helper taking the member re-reads it (Zoo 31).
4. **Sibling comparison:** when two functions share a shape and one matches, the difference is in the source of
   the other, not the compiler (Zoo 90). JPOG has many twins (TVector2/3/4, TGUI property sets).
5. **Nothing filed as compiler-limited is final.** Zoo re-opened all of its "final" entries; most were source
   (Zoo current state, 2026-11-03). JPOG's own re-examination after those findings matched four (MATCHING_NOTES
   "Re-examination"). Re-test COMPILER_LIMITED.md entries with the leads above in mismatch sessions.

## Code-shape evidence that holds for any compiler

- `test al,al` (or `test eax,eax` on a byte) right after a call: the callee returns bool (Zoo 91).
- A null test whose register is then the return value: an early `return 0;` before the local is set (Zoo 60).
- Registers copied before pushing (`mov ecx,ebx / push ecx`): a small non-POD struct passed BY VALUE (Zoo 56).
- `neg` then one `sub` per term: the first term is a local (`long v = -f(); x = v - a - b;`), not one expression (Zoo 64).
- Never put the call inside a logging macro's arguments when the original calls first and pushes the format after (Zoo 7).

## Tools and methods Zoo uses that JPOG can too

- Notes\OPEN_WALLS.md style: one row per wall with its history, so later sessions do not repeat the same tries.
- Throw-away calibration variants before guessing a source shape (Zoo 66, 95).
- Tools\inlinecheck.py (both projects): every function we call out of line that the original never calls - the
  automated form of JPOG's own "header inlines and call-site evidence" method.
