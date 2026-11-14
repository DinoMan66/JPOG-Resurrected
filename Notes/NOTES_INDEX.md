# Index of MATCHING_NOTES.md (37 KB, 45 entries)

Made by Tools/notes_index.py - do not edit; re-run it after adding notes. Read an entry with
`python3 -I Tools/notes_index.py Notes/MATCHING_NOTES.md --show <id or heading words>`.

| Entry | Lines | Size | First sentence |
|---|---|---:|---|
| section | 3-8 | 0.4 KB | Target - Installed game files (NOT the `Setup\` folder - that is an older, Jan-14-2003 build set) |
| section | 9-15 | 0.6 KB | Toolchain (verified: |
| section | 16-16 | 0.0 KB | Compiler habits learned |
| 1 | 17-20 | 0.3 KB | Exported classes are `__declspec(dllexport)` |
| 2 | 21-21 | 0.1 KB | `-Gz` => free functions are `__stdcall` |
| 3 | 22-23 | 0.2 KB | Toshi-DLL imports are `dllimport` |
| 4 | 24-25 | 0.1 KB | Boolean tests are written `x == true` |
| 5 | 26-26 | 0.1 KB | By-value class parameters are destroyed by the callee |
| 6 | 27-28 | 0.2 KB | Inlined smart-pointer code re-checks null after storing |
| 7 | 29-30 | 0.2 KB | Replacement `operator new/delete` are defined per DLL |
| 8 | 31-32 | 0.1 KB | Loops and branch targets are 16-byte aligned with multi-byte NOPs (`lea esi,[esi+0]`) - automatic |
| section | 33-37 | 0.4 KB | Tooling pitfalls we hit - A stray `X.h` next to `X.cpp` silently overrides `include\X.h` (quoted includes search the . |
| section | 38-38 | 0.1 KB | More habits (TInputInterface / TInputDXInterface, Oct 2026) |
| 9 | 39-41 | 0.3 KB | Small virtuals are inline in the class body |
| 10 | 42-44 | 0.3 KB | Hidden loads through `const int&` |
| 11 | 45-46 | 0.2 KB | Real 4-byte float stack temporaries |
| 12 | 47-48 | 0.2 KB | switch statements |
| 13 | 49-50 | 0.2 KB | Loop tests through inline bool helpers |
| 14 | 51-52 | 0.2 KB | Ternaries matter: |
| 15 | 53-54 | 0.2 KB | Out-of-range "if" bodies: |
| 16 | 55-58 | 0.3 KB | Unresolved (register allocation): |
| section | 59-65 | 0.5 KB | Build automation (current) - `Src\<Dll>\*.cpp` per DLL, shared `Src\include` |
| section | 66-66 | 0.1 KB | PPropertyParser findings (rounds 13-18, 2026-10-17) |
| 17 | 67-69 | 0.3 KB | Exported static pointer members are declared `static const T* X;` (no second const) |
| 18 | 70-71 | 0.2 KB | Pooled-string copy constructors clear first |
| 19 | 72-74 | 0.3 KB | Intrusive reference counts of TObject-derived classes live in a second base class |
| 20 | 75-77 | 0.1 KB | Ternary vs `if` inside tiny inline accessors (GetCString) made no difference - the block order there comes from somewh |
| 21 | 78-89 | 1.1 KB | Toshi's pooled/localised string destructors and assignments are NOT inline functions |
| 22 | 90-93 | 0.3 KB | Token types (TFileLexer::TokenType) come from TFileLexerUTF16::tostring and PPropertyWriter::PutToken: |
| section | 94-99 | 0.3 KB | Infrastructure notes - The device file bridge can serve a CACHED copy of a file that keeps the same name/size: |
| section | 100-117 | 2.0 KB | #23 Compiler build and original source layout (2026-10-17, round 39) - Every shipped (`*_inst.dll`, 2003-02-07) DLL em |
| section | 118-140 | 2.2 KB | #24 TRenderInterface rules (rounds 33-38) - Implicit copies: |
| section | 141-154 | 1.2 KB | TKernelInterface (rounds 089-092, 2026-10-28) - Src\TKernelInterface\flags.txt is EMPTY: |
| section | 155-174 | 1.8 KB | TKernelInterface (rounds 093-122) - Kernel classes are `__declspec(dllexport)`; |
| section | 175-201 | 2.8 KB | TKernelInterface (rounds 123-178, second long session) scoreall: |
| section | 202-212 | 1.0 KB | TKernelInterface (rounds 180-188, 45-minute session) scoreall: |
| section | 213-242 | 3.6 KB | TGuiInterface (rounds 192-208, 100-minute session, written from scratch) scoreall: |
| section | 243-255 | 1.4 KB | Mismatch clean-up (round 226) - Wrong-target matches fixed: |
| section | 256-285 | 3.3 KB | Header inlines and call-site evidence (rounds 228-240) - The original's exported copies of header inlines sit together |
| section | 286-299 | 1.3 KB | GUI property sets and bool spelling (rounds 247-251) - A bool built with branches in the original (`test; |
| section | 300-307 | 0.7 KB | Inlined null tests and accessor spelling (rounds 252-253) - `if (!p) return empty; |
| section | 308-319 | 1.2 KB | Re-examination after the Zoo Tycoon findings (rounds 254-257, 2026-11-03) - A base-class pointer conversion (`TGeneric |
| section | 320-342 | 2.1 KB | Kernel files, tasks and lexer (rounds 361-382, 2026-11-13) - `<windows.h>` defines `CreateFile` as `CreateFileA`, whic |
| section | 343-350 | 1.1 KB | PGUICore start, accessor-only classes (rounds 388-400, 2026-11-13) - Accessor-only classes compile fine with offset-na |
| section | 351-367 | 3.5 KB | PGUICore, widget lists and menu classes (rounds 401-462, 2026-11-13) - TNode/TNodeList offsets: |
