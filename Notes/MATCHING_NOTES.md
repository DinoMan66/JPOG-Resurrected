# JPOG / Toshi matching notes

## Target
- Installed game files (NOT the `Setup\` folder - that is an older, Jan-14-2003 build set).
- 18 code files link-dated 2003-02-07 (engine DLLs + `SimJP.exe`); third-party: binkw32, fmod, libmmd.
- Source paths live inside each DLL's compiler banner (see `JPOG_source_files_installed.txt`), e.g.
  `Z:\Toshi\Source\TApplication\TApplication.cpp`, `Z:\Toshi\Projects\<Name>\Win\Final\<Name>.pdb`.

## Toolchain (verified: TApplication.dll 20/20 matching)
- Intel C++ 5.0.1 build 010525Z (game was built with 020125Z - no visible difference so far) + Visual C++ 6.0.
- Flags: `-Qvc6 -nologo -Gz -MD -W3 -vmg -vmm -Zi -O2 -D TOSHI_SKU_WINDOWS -D WIN32 -D _WINDOWS
  -D _UNICODE -D TOSHI_FINAL -D NDEBUG -D USER_JPBUILD` (per-DLL differences are listed in the build notes).
- Workflow: write C++ on the PC -> `tools\build.bat` in the XP VM -> copy `results\*.txt` back ->
  `py tools\compare.py original\X.dll results\X.txt --map notes\X.map --tracker notes\function_tracker.csv`.

## Compiler habits learned
1. **Exported classes are `__declspec(dllexport)`.** Evidence: the DLL exports the vtable (`??_7...`) and every
   member. Effect on codegen: the compiler emits the *vector deleting destructor* (`??_E`) in vtable slot 0.
   Without it you get the scalar one (`??_G`), which will not match. The array operators / array new alone do not
   trigger it.
2. **`-Gz` => free functions are `__stdcall`** (`YG` in decorated names). `operator new/delete` stay `__cdecl`.
3. **Toshi-DLL imports are `dllimport`** (`call dword ptr [__imp_...]`). Declare imported members with
   `__declspec(dllimport)` (macro `TOSHI_API`), either per member or per class.
4. **Boolean tests are written `x == true`** (`cmp al,1` in the binary), and "return" shapes follow
   `if (!x) return false; return true;`.
5. **By-value class parameters are destroyed by the callee** (`ret 8` + destructor call inside the function).
6. **Inlined smart-pointer code re-checks null after storing** (extra `je` right after the store). Reproduced by
   `if (m_p) m_p->m_refCount++;` inside the "if (o.m_p)" branch.
7. **Replacement `operator new/delete` are defined per DLL** (non-exported): `tmalloc(size, 0, -1)` / `tfree(p)`.
   Define them before first use so the constructor and Create() inline the call.
8. Loops and branch targets are 16-byte aligned with multi-byte NOPs (`lea esi,[esi+0]`) - automatic.

## Tooling pitfalls we hit
- A stray `X.h` next to `X.cpp` silently overrides `include\X.h` (quoted includes search the .cpp's folder first).
- `dumpbin /disasm` shows no symbol for calls inside the same object -> `compare.py` detects `E8` calls by opcode.
- Copying a folder into a folder with the same name creates `Tools\tools\...`; keep the layout flat.

## More habits (TInputInterface / TInputDXInterface, Oct 2026)
9. **Small virtuals are inline in the class body** (e.g. `Flush() { return true; }`,
   `IsForceFeedbackDevice() { return false; }`, `SetVibration(...) {}`). Evidence: a derived class in
   ANOTHER DLL has its own local (non-exported) copy in its vtable instead of an import thunk.
10. **Hidden loads through `const int&`**: `TMath::Max/Min` take and return `const T&`; with a named
    static const the binary compares against memory (`cmp eax,[STICK_DEADZONE]`) while plain
    arithmetic with the same constant is folded. Static consts must be DEFINED before use in the .cpp.
11. **Real 4-byte float stack temporaries**: binding a call result to `const float&` gives `fstp dword`;
    plain `float x = f();` gives an 8-byte spill (`fstp qword`). Stack slots follow declaration order.
12. **switch statements**: case bodies come out in REVERSE source order (ascending source -> descending code).
    `tools/switchgen.py DLL RVA --order value` rebuilds `case K: return C;` switches from the jump table.
13. **Loop tests through inline bool helpers** (e.g. `DeviceList::IsValid(d)`) produce `setne/test` pre-tests;
    the same comparison written inline does not.
14. Ternaries matter: `return (f < -0.5f) ? -1 : ((f > 0.5f) ? 1 : 0);` differs from if/return chains;
    `(x == true) ? 0 : 1` gives `cmp al,1 / je` where `(x != true)` gives `setne`.
15. Out-of-range "if" bodies: ICC lays out `if (FAILED) {...}` vs `if (SUCCEEDED) {...}` differently; when
    the success path is the fall-through, write it first.
16. Unresolved (register allocation): TArray iterator loops (StartRepeat/StopRepeat/Latch/Unlatch/IsLatched,
    ProcessRepeats, SetCapacity) keep the iterator in memory with write-through in the original. Many
    variants tried (operator forms, copy ctors, named returns) without success - revisit later.

## Build automation (current)
- `Src\<Dll>\*.cpp` per DLL, shared `Src\include`. Results are `Results\<Dll>.<file>.txt/.rel` plus one
  bundle `Results\ALL.txt` (`tools/unbundle.py` splits it). `compare.py` reads exact relocations from `.rel`.
- One-shot experiments: `Src\<Dll>\VarX_<file>.cpp` = `#define VAR_X` + `#include "<file>.cpp"`; deleted by
  the build after compiling. Score them with `tools/varcmp.py DLL MAP "res/*.txt" names...`.
- `Tools\queue\cmd.bat` (optional) is run once inside the VM before compiling; output in `Results\cmd.txt`.

## PPropertyParser findings (rounds 13-18, 2026-10-17)
17. **Exported static pointer members are declared `static const T* X;` (no second const)**. ICC then mangles
    them `2PBV...@B` exactly like the original and loads them from memory at each use. With `const T* const`
    it mangles `2QBV...@B` and constant-folds the address (`push offset`), which never matches.
18. **Pooled-string copy constructors clear first**: `m_p = 0; if (o.m_p) { m_p = o.m_p; if (m_p) ++count; }`
    (the if/else form gives a different block order).
19. **Intrusive reference counts of TObject-derived classes live in a second base class** (`TRefCountBase`,
    ctor stores 0 before the vtable), like TInputInterface's +4 base. Members declared before an embedded
    list must be set in the mem-initializer list to be stored before the list's own constructor runs.
20. Ternary vs `if` inside tiny inline accessors (GetCString) made no difference - the block order there
    comes from somewhere else (still open).

21. **Toshi's pooled/localised string destructors and assignments are NOT inline functions.** The
    original calls a local out-of-line copy of ~TPCString in every translation unit (0x1bf0 in
    PProperties, 0x3190 in PPropertyName, 0x5820 in PPropertyReader, 0x76f0 in PPropertyValue), plus
    local copies of TPCString/TPWString/TLString operator= and the TPWString/TLString destructors in
    the PPropertyName, PPropertyReader and PPropertyValue units. Nothing made ICC stop inlining an
    `inline` function (tried: explicit/qualified dtor calls, late definitions after the callers,
    dllimport class, `__inline`, different body shapes). Defining the function out-of-class WITHOUT
    `inline` does it (round 25: Error/Warning/SkipBlock/ParseError dtor matched at once, 136 -> 167
    after round 26). The assignments are inlined in the PProperties/PPropertyBlock units (SetName,
    SetComment...) but not in the other three, so those three .cpp files define
    TOSHI_STRING_ASSIGN_NOT_INLINED before their includes. Caveat: plain definitions in a header
    would collide when linking several objects; a linkable build needs per-file copies (to do).
22. Token types (TFileLexer::TokenType) come from TFileLexerUTF16::tostring and PPropertyWriter::PutToken:
    0 EOF, 1 ';', 2 ':', 3 ',', 4 '.', 5 '*', 6 '$', 7 '[', 8 ']', 9 '{', 10 '}', 11 '(', 12 ')',
    13 '<', 14 '>', 15 '=', 0x10 IDENT, 0x11 STRING, 0x12 INTEGER, 0x13 UINTEGER, 0x14 FLOAT, 0x15 COMMENT.

## Infrastructure notes
- The device file bridge can serve a CACHED copy of a file that keeps the same name/size: always write a
  build request from a uniquely named local file (`queue/req_<round>.txt`) and judge Results by mtime,
  not by DONE.txt's content.
- Ghidra exports for every DLL are in the PC's `decompiled\` folder (Tools\export_all.bat).

## #23 Compiler build and original source layout (2026-10-17, round 39)
- Every shipped (`*_inst.dll`, 2003-02-07) DLL embeds the Intel compiler's per-object comment record:
  `Intel(R) C++ Compiler for 32-bit applications, Version 5.0.1 Build 020125Z : Z:\Toshi\Source\TRender\TAnimation.cpp : -Qvc6 -Qlocation,link,... -Qvc6 -Qlocation,link,... -nologo -Gz -MD -W3 -vmg -vmm -Zi -O2 -I Z:\Toshi -I Z:\Toshi\Include -D TOSHI_FINAL -D NDEBUG -D TOSHI_SKU_WINDOWS -D WIN32 -D _WINDOWS -D _UNICODE -D USER_JPBUILD -FoFinal/ -FdFinal/ -c`
  (PPropertyParser adds `-I Z:\Toshi\Plugins\Include -FD`).
- Our VM compiler is **5.0.1 Build 010525Z** (C:\ICC501). The game used **Build 020125Z**: same version, a later update. Flags are identical.
- Inlining differs (original never inlines one non-inline function into another: ~TKeyframeLibraryInstance->Destroy,
  TAnimation::GetSequencePtr->TSkeleton::GetSequence(int), TResource::IsValid->IsCreated, TResource::SetName->GetUId).
  No switch reproduces it (tried -Ob0/-Ob1, -Qip-, -Qip_no_inlining, -Qip_no_inlining -Ob1, #pragma auto_inline(off),
  header-inline definitions, -O1, -Os, -G5/-G6/-G7). -G6 = our default. Most likely a heuristic change between the builds.
- The non-`_inst` copies of some DLLs (e.g. TRenderInterface.dll, 2003-01-14) are a different build: `-D TOSHI_RELEASE
  -D USER_AHATT -D TOSHI_SKU_WINDOWSMFC` (ReleaseMFC). Always match against `_inst`.
- The records list the original source files. TRenderInterface (Z:\Toshi\Source\TRender\): TAnimation, TCameraObject, TDBase,
  TDImp, TDebugText, TEnvironment, TGFXFileInstanceObject, TGFXFileObject, TIndexFactoryResourceInterface,
  TIndexPoolResourceInterface, TJPShadowFudgeNode, TLightingNode, TMaterialLibrary, TModel, TRenderAdapter, TRenderCapture,
  TRenderContext, TRenderInterface, TResource, TResourceNameMap, TScene, TSceneObject, TSceneSysMesh, TShader, TTerrainObject,
  TTextureFactory, TTextureResource, TTransformObject, TVertexFactoryResourceInterface, TVertexPoolResourceInterface, TViewport (.cpp).
  Our Src\<Dll> files should use exactly these names.

## #24 TRenderInterface rules (rounds 33-38)
- Implicit copies: TVector*/TQuaternion/TMatrix44 have no user copy operators. Two adjacent 16-bit fields that the original
  copies as one dword are a union with a 32-bit member.
- TObject: class-level dllimport (the inline copy ctor reads TObject's vtable through the import table) and a private,
  undefined operator= (no TObject-derived class exports one).
- TNodeTree/TNodeList node constructors store the links first and the owner pointer last. TNodeTree::Insert writes
  `node->m_pPrev->m_pNext = node` (it reuses the value just stored).
- TResource::Parent: `tree = m_pTree; parent = m_pParent; if (parent == 0 || parent == tree->GetRoot()) parent = 0; return parent;`
- TQList::InsertTail links through the node, like InsertHead: `p->m_pPrev = m_oHead.m_pPrev; p->m_pPrev->m_pNext = p;`
  (the original keeps the old tail in a register; matched PutProperty x2 and PutPropertyUnique, round 85).
- PProperties::PutPropertyUnique(name, value, comment) is a full copy of PutProperty's body, not a call to it - so the
  TPCString overload calls it instead of PutProperty (that was the one wrong-target match).
- ICC's layout of `if (!p) return x;` vs `p ? a : b` does not follow the spelling: swapping/rewording did not change
  GetRequiredProperty, operator==(const char*) or TPCString::GetCString (round 85). "Condition inverted" here is
  most likely the compiler build (see #23) - don't spend attempts on swapping if/else bodies.
- Experiment chains (`#if defined(VAR_A)`, TML_POS, TKF_FORM) were resolved to their active branch on 2026-10-28;
  resolve any new chain with Tools\bake.py in the same session. Still open: TQLIST_FORM - TAnimation compiles
  TQList.h with form 3, PPropertyParser with form 0; one real header has one form.
- Iterators (TNodeList / TQList): operator== / operator!= take the iterator BY VALUE - with `const Iterator&` ICC
  keeps the temporaries in memory (an 8-byte frame the original does not have). Some loops also cache
  `Iterator end = list.End();` before the loop (GetMaterial, PProperties::GetProperty); the others build End()
  per comparison. Fixed 4 functions in round 88 with no regressions in the 9 files that use these lists.

## TKernelInterface (rounds 089-092, 2026-10-28)
- Src\TKernelInterface\flags.txt is EMPTY: the kernel is built without `-Qsfalign` (with it every function starts with
  `push ebx / mov ebx,esp / and esp,-16`). Round 089 was lost to this; its attempt counts were discarded, not committed.
- Kernel build uses the shared headers: each .cpp starts with `#define TOSHI_KERNEL_BUILD` and
  `#define TOSHI_API __declspec(dllexport)`. TOSHI_EXPORT (TVector.h) is `dllexport` only in that build, so a class
  marked with it also emits its inline members (TPlane, TAABox); in all other modules it is empty.
- TAABox is centre (+0x00) and half-extents (+0x0C), not min/max. TPlane::PlaneComparison returns -1 / 0 / 1
  (enumerator names are invented).
- Inline members that the original calls out-of-line (TVector3::Set(x,y,z) called by the (x,y,z) constructor) cannot be
  written in the .cpp while TVector.h defines them inline for the other DLLs; they are skipped for now.
- Float compares against a constant in memory (`fld dword [0x100441e4]`, value 0.0f or 1.0f) are not the literal: a
  literal 0.0f becomes fldz / a double constant. TAABox::ComparePlane, TVector3::Divide(float) and Normalise need that
  global float identified first.

## TKernelInterface (rounds 093-122)
- Kernel classes are `__declspec(dllexport)`; .cpp files define TOSHI_API (and often TOSHI_KERNEL_BUILD) before including
  headers. Mangling encodes access and calling convention, so header declarations must match exactly.
  Kernel-internal headers: TKernelMisc.h (TMath/TSystem/TBitArray/TRandom), TKernelContainers.h, TGenericLists.h,
  TKernelFiles.h, TKernelClass.h, TKernelSystem.h.
- Float constants: write the literal (`1.0f / s`, `== 0.0f`); it matches the original's memory-constant load.
  An exported constant (TMath::PI) must be defined in its own .cpp (TMathData.cpp) or the compiler folds it.
  Read other constants from the PE (section reader on Original\DLLS\TKernelInterface_inst.dll, base 0x10000000).
- Layouts: TFile vtable +0, filesystem +4 (TNullFile count +0xC; TMemFile buffer +8, cursor +0xC, size +0x10;
  TISOFile start +8, size +0xC, pos +0x10). TClass 0x28 bytes (name, create, createInPlace, init, deinit, parent +0x14,
  version +0x20, static-initialised +0x24). TCString/TWString: buffer +0, 24-bit length / 8-bit excess at +4.
- Oddity to review: TMath::LineVsLine2D(..., TVector2& hit) only matched as `bool found = LineVsLine2D(a,b,c,d,t);
  if (found == true) {...}`. Not a fakematch (no dummy values), but the `== true` is unusual.
- Tooling lesson: the first device commit after an edit sometimes wrote stale content; always compare sizes with a
  directory listing and recommit.
- Filed after 2/2 (regalloc/shrink-wrap/sched): TCString/TWString Copy, AllocBuffer, Format, Concat, FindReverse;
  TMatrix44 RotateX/Y/Z, TransformVector, RotateVector; TMath PointVsPlane2D/2DF/3D, LineVsLine2D(float&),
  ClosestPointOnLine2D; TVector2 operator/(float). Still DIFF at 2/2: TCString/TWString Truncate, TVector3::IsNormalised.
- Unwritten categories are listed in CLAUDE.md "Current state".

## TKernelInterface (rounds 123-178, second long session)
scoreall: 537 matched at session start, 849 at round 178 (594 not written yet, 117 open differences).
- TU-split rule: ICC inlines small same-TU callees. Where the original calls an out-of-line function, put the
  caller in a different .cpp from the callee. Splits: TCStringCtors.cpp, TMalloc.cpp, TMemoryProcess.cpp,
  TNodeListCalls.cpp, TNodeListIsEmpty.cpp. Not strictly order-dependent (DeleteAll still calls IsEmpty).
  Side effect: splitting the TCString ctors made TCString::operator+ (x3) filed at 2/2 and TCString::Mid HUMAN (4/2,
  frame 0x14 vs 0xc).
- Opposite case (TDList.cpp): the original has TNode unlink fully inlined; open-coding it in the member
  (TGenericPriList::RemoveTail/RemoveHead) matched. Same tried for TGenericDList::RemoveAll in round 178 (not reported MATCH).
- Stale commits: always restage and compare `wc -c` after a device commit; recommit on mismatch.
- Default TCString ctors must assign m_pBuffer=m_aNull; m_iStrLen=0; m_iExcess=0 explicitly (a Reset() call stays out of line).
  IsAllLowerCase/IsAllUpperCase return true for empty strings.
- TMemory::SetProcess: slotBits=(block->m_pSlot - GetMemManager().m_aSlots)<<27 first, then `| size | 1 | m_uGlobalFlags`.
  Deinitialise uses `if (m_bInitialised == true)`, a file-static s_pMutex (0x10043040) declared before s_pMemManager (0x10043044).
- TRandom layout: seed +0, count +4, results[16] +8, memory[16] +0x48, accumulator +0x88, last result +0x8c, counter +0x90 (0x94).
  REVIEW FLAG: Isaac/RandInit use ISAAC_IND/ISAAC_STEP/ISAAC_MIX statement macros; check against the readability rule on macros.
- TDebug::MSGLEVEL enum names are invented (default level 2). TDebug_Message(level,...) is DIFF 1/2 (original loads level first).
- TPile sizeof(int) quirk, TObject/TClass internals, libm precision-control-word wall, inline-asm FPU helpers (unwritable),
  Yield macro, friend-class list linking, virtual ~TFile: see earlier sections and COMPILER_LIMITED.md.
- Filed after 2/2: TFreeList ctor, MapSizeToFreeList, GetInt(int)/GetInt(min,max), Copy(TWString/TWChar*, int),
  UnmountFileSystem, DeleteHead/DeleteTail. DIFF 2/2: TUser::Deregister, Isaac. DIFF 1/2: IsIndexValid, TISOFile::Seek, TDebug_Message.
- Unwritable: compiler-generated copy ctors/assignments, header-inline TVector/TQuaternion/TPlane/TSphere, TNodeTree/TDList template
  users, TTask/TScheduler/TLocale/TPCString pools, libm wrappers, TThread ctor, TMemory ctor/dtor/Free, TFileLexer, TProfiler.
- Anti-cheat after round 178 failed on inline `__asm` in TMath.cpp and the ISAAC statement macros in TRandom.cpp. Round 179 removed the
  asm functions (FloatToInt, RoundToInt, Round, Set/GetFPUControlWord stay unwritten) and replaced the macros with static functions
  IsaacIndex/IsaacStep/IsaacMix. Isaac DIFF 3/2, RandInit DIFF 1/2. Never write `__asm` or statement macros, even to match.

## TKernelInterface (rounds 180-188, 45-minute session)
scoreall: 843 at round 179 -> 876 at round 188 (569 not written yet, 115 open, 1 HUMAN: TCString::Mid).
- Inline destructor rule: `~TGenericDList() { RemoveAll(); }` is defined in the header. The original's containing destructors
  (TThreadManager, TGenericEmitter, TFileManager) call RemoveAll directly, so they must not call it again by hand.
- Out-of-line constructors that call a base/member constructor or a sibling function go in their own .cpp (TDListLifetime.cpp,
  TRandomInit.cpp, TISOFileCtor.cpp): the TU-split rule again.
- Mangled access letters are evidence: TISOFile::Close is 'I' (protected). TDebug::OpenDebugFile calls
  GetDateFormatA(LOCALE_SYSTEM_DEFAULT, LOCALE_NOUSEROVERRIDE) into an unused 1000-byte buffer.
- TNode::Remove(int) (TGenericNTree) matched only with the unlink open-coded; TGenericDList::RemoveAll matched open-coded too.
- Stale device commits happened again several times: always restage and compare sizes.

## TGuiInterface (rounds 192-208, 100-minute session, written from scratch)
scoreall: 22 at round 192 -> 219 at round 207 (903 not written yet). One header per class in Src\include, bodies in Src\TGuiInterface.
- TArray(grow, capacity) stores count, then grow, then capacity; the TArray.h change is shared. SETCAP 6 gives the AddEmpty variant that
  uses Max(m_capacity + m_grow, m_count + 1) (TGUIComponentInfo.cpp defines it before including the header).
- Overloaded virtuals get vtable slots in REVERSE declaration order (TGUIDisplayContext::PushRotation): declare the 3-argument overload first.
- `new T(*this)` in Clone calls the implicit or declared copy constructor; `delete p` after `if (p)` gives a double null test.
- A class that derives from a polymorphic T through TNodeList<T>::TNode (TGUIComponent) puts the node at +4, and casts back to T* adjust the pointer.
- Class boilerplate (GetClass, CreateObject, CreateObjectInPlace, InitialiseStatic, DeinitialiseStatic, TClass m_sClass) is written out by hand in
  every class; do not stamp it with a macro. Abstract classes return 0 from both factory functions.
- ICC inlines a constructor into CreateObject/CreateObjectInPlace when it is defined earlier in the same file (TGUIEffectManager): put it after them.
- A member that the original constructor does not initialise (TGUIElement's TLString label, constructed by hand in ChangeType) has to be raw
  storage, or the implicit constructor initialises it. Give such a class a real out-of-line constructor, destructor and operator=, otherwise the
  components that embed it inline the constructor and the callers diverge (all five TGUI*Component classes).
- Components allocate from the GUI memory pile: TGUIComponent has operator new (TGUINew) and operator delete (TGUIDelete) plus a placement new
  (name hiding would otherwise hide the global one in CreateObjectInPlace).
- Bridge caching: committing a file under a staged path that was committed before can write the OLD content (TGUIFrameComponent.h). After a
  commit that does not seem to take effect compare sizes with device_list_dir and recommit from a new staged path.
- TU-split rule (rounds 209-210): a default constructor defined in the same file as CreateObject/CreateObjectInPlace gets inlined into them. Put it in a
  file of its own (TGUIComponentConstructors.cpp) and the factories call it, as the original does.
- Every class that has operator new/delete of its own (TGUIComponent, TGUIWidget, TGUIStyle) also exports the inline operator new[]/delete[]
  (??_U / ??_V); the symbols show up in the tracker as UTGUIxxx / VTGUIxxx.
- TGUIWidget (rounds 212-220): the exported name of the state setter is SetState(unsigned int, unsigned int); the SetSelected/SetEnabled family calls it
  with `on == true ? mask : 0` (the original compares the bool with 1, `if (on)` gives test al,al). A pure virtual slot missing from the header shifts
  every later vtable offset by 4 (Clone was slot 13): when a call through [edx+0xNN] is off by 4, count the slots again.
- A function that forwards to its parent returns 0, not its argument, when there is no parent (TGUIWidget::AllowsFocus): read the `xor eax,eax` at the end.
- TGUITextureSection: bitfields in an unsigned char container (rotation:2 at +0x20; wrap, mirrorX, mirrorY at +0x24) give exactly the original
  read-modify-write code for the setters and the `and/test/setne` idiom for the bool getters.
- Placement new: files with a CreateObjectInPlace for a class without operator new of its own must include TNewDelete.h.
- TGUIWindow::NotifyParentChange calls TObject::IsA on the parent and ignores the result; not written (it would need an empty if body).

## Mismatch clean-up (round 226)
- Wrong-target matches fixed: TCString/TWString operator+ used `TCString result; result.Copy(*this)`, which emits a call at the same
  place but to the default constructor. The original inlines the copy constructor (`Reset()` call + `Copy`) and the destructor
  (`FreeBuffer()` call). Every function that returns a string by value (member and free operator+, Mid) now lives in TCStringCtors.cpp
  with the copy/convert constructors and both destructors, written plainly as `TCString result(*this); result.Concat(s, -1); return result;`
  (operator+(const char*/TWChar*) converts the operand: `result.Concat(TCString(s), -1)`) and `return part;` in Mid.
  TCString.cpp keeps the default/sized constructors (now also TWString's). Round 226: 886 -> 900 matched, no regressions.
- TCString::Mid / TWString::Mid now have the original call set and frame; only the `start + len > total` compare comes out with its
  operands swapped (cmp eax,edx/jge vs cmp edx,eax/jle). TWString::Mid filed.
- Round 227: TCString::Mid MATCH. The `int total = m_iStrLen;` local (assigned in both branches, a Ghidra-style merge) was the cause:
  comparing against the member directly (`start >= m_iStrLen`, `start + len > m_iStrLen`, `len = m_iStrLen - start`) gives the
  original operand order. ICC keeps source operand order against a member, but puts a computed sum second against a local.

## Header inlines and call-site evidence (rounds 228-240)
- The original's exported copies of header inlines sit together in "inline clusters" (e.g. TKernelInterface 0x7280-0x7ad0:
  every TGenericDList/TGenericPriList member, TThreadManager ctor, TRefCounted; TGuiInterface 0x6e10-0x7400: TGUIComponentInfo
  accessors and the whole TGUIFunction family). A function there that the original never calls out of line is an in-class inline.
- Method: take every REL32 call target in our Results\*.rel files and keep the exports the original never calls (count the
  `call 0x...` targets in an objdump of the original). Every hit so
  far was a missing inline: TFile/TNativeFile/TISOFile::GetFileSystem, TGenericDList ctor (+ TNode ctor defined after the class),
  TGenericPriList::TNode::Remove, TQuaternion::SetInverse/SetConjugate, MemBlockSlot, TGUIColour(EEEE)/operator=,
  TGUIDeserialisable copy ctor, TGUIPropertySpec::GetSourceClass, TGUIStyleState::AddComponent, TAnimation/TSkeletonInstance
  ctors, ~TRenderCapture. (Ignore hits that come only from SECREL/debug relocations.)
- An exported inline copy does not inline a callee defined later (TGenericDList() calls TNode() out of line because TNode() is
  defined after the class; Clone calls the implicit copy constructor out of line). Same rule as the TMatrix44 ctor16 -> Set case.
- Our compiler also inlines a same-file constructor into CreateObject even when the constructor is defined later in the file
  (TGUIEffectManager): keep the factories in a second translation unit (TGUIEffectManagerCreate.cpp).
- TMemory is two TNodeList<MemBlockSlot> (used +0x00, free +0x10) and 32 slots; MemBlockSlot derives from TNodeList<>::TNode.
- ISO9660Directory is 0x38 bytes (name[0x24] at +0x14), ISO9660File 0x34; TISOFileSystem has the directory array at +0x104 and its
  count at +0x108 (sizes from the original operator= copies and the imul 0x38 in the constructor).
- TGUIWidget::AllowsFocus returns 0 (not `from`) when there is no parent - a plain source bug found from the size difference.
- Tried and rejected: -Qpc32 and -Op on TMath.cpp (neither produces the fnstcw/fldcw 0x27f bracket around the libm calls; -Op
  breaks 18 other TMath functions). TArray::AddEmpty `m_count++; return m_data[m_count - 1];` matches TSumOfMinterms::operator+
  but breaks TResourceNameMap::AddItem, so the shared header keeps `return m_data[m_count++];`.
- Ternary arm order: our build lays `c ? A : B` out as `test; j!c ->B; A; jmp; B:`. When the original has the other arm
  falling through, invert the condition (`(value == 0) ? TYPE_UNDEF : &value->GetClass()` matched PPropertyValue(TObject*)).
  Swapping an if/else does NOT move blocks the same way (TQuaternion::Lerp, TSphere::ComparePlane unchanged), and our build
  merges identical tails / `return false` epilogues that the original keeps separate (TGUIElement::IsDefined, PutToken).
- `if (Can...()) { ...; return true; } return false;` instead of an early `if (!Can...()) return false;` put the failure
  block at the end like the original (PPropertyValueArray::GetTVector3 / GetTQuaternion).
- Formatting rule (anti-cheat 2026-10-29 21:55): one statement per line. The ISAAC mix in TRandom::RandInit was first written
  with three statements per line, as in the reference code, and was flagged as "packed"; it is now one statement per line.

## GUI property sets and bool spelling (rounds 247-251)
- A bool built with branches in the original (`test; jne; mov bl,1; jmp; xor bl,bl`) is spelled `cond ? true : false`; a plain
  `bool b = a == c;` gives setcc in our build (PPropertyReader::LoadPropertyBlock x2). TNodeList::TNode::IsLinked is
  `(m_pList != 0) ? true : false` for the same reason (TGUILayoutInfo/TGUIWidgetInfo destructors; no TRender regressions).
  The reverse also exists: a bool the original keeps in a register with setcc (TGenericFifo::Push/Pop `signalled`).
- TSortedArray<T, Comparator> (include/TSortedArray.h) derives from TArray<T>; GetPropertyInfoOrderedSet (vtable slot 12,
  was vf12) returns the protected static ms_oPropertySetOrdered. The ms_oPropertySet statics are protected (mangled `1`).
- TGUIPropertySpec has a vtable (+0), virtual destructor, five constructors and operator=. operator= tests the TARGET's kind and
  the copy constructor skips the sort hint - both as in the original.
- `if (p != 0) delete[] p;` when the original shows two `je` (one from the if, one from delete[]'s own null test);
  plain `delete[] p;` when it shows one.
- DeinitialiseStatic: the original keeps the TArray iterator in memory (frame 0xc); our build keeps it in registers
  whatever the spelling - compiler-limited (TGUIStyle/TGUILayoutManager/TGUIWidget/TGUIWindow).

## Inlined null tests and accessor spelling (rounds 252-253)
- `if (!p) return empty; return p->x;` and `p ? p->x : empty` lay out the same once inlined: our ICC puts the null
  block after the function body, the original's falls through after `test; jne`. Spelling does not move it
  (PPropertyValue::operator==, PPropertyWriter::Put(TPCString), IsEmpty's TLString branch): code generation.
- TLString has no GetWString: the kernel exports operator*, operator->, operator const TWString* and
  GetLocalisedString, all null-first on both levels (TLString.h now has them).
- Splitting `if (a || b) return true;` into two ifs duplicates the return block (string_needs_quotes): keep the `||`.

## Re-examination after the Zoo Tycoon findings (rounds 254-257, 2026-11-03)
- A base-class pointer conversion (`TGenericDList::TNode* node = derived;`) costs a null test when the base is not at
  offset 0; the original has none, so it converted through a reference (`TNode& node = *derived;`). Matched
  TFileManager::UnmountFileSystem and TThreadManager::RemoveThread, both filed as "regalloc" before.
- Static helpers meant to replace a macro must be `static inline`; plain `static` ones stay calls (TRandom::Isaac now has
  the original's length and call set; register choice left).
- TGUIIconComponent's default constructor joins TGUIComponentConstructors.cpp (CreateObject/CreateObjectInPlace match).
- About 25 open functions show the original calling a small non-inline function of the same file that our compiler
  inlines (#23). They are listed in NOT_MATCHING.md; only a translation-unit split would hide the body from our compiler.
- TRandom::GetInt(int, int): the original's ebp frame, every value in a stack slot and `mul dword ptr [local]` are
  what this compiler emits for a function containing inline assembly. Left as a mismatch (no `__asm`, user decision).

## Kernel files, tasks and lexer (rounds 361-382, 2026-11-13)
- `<windows.h>` defines `CreateFile` as `CreateFileA`, which renamed the exported `...::CreateFile` methods in every file that
  includes it. `#undef CreateFile` right after the include in TKernelThreads.h / TKernelDLL.h; Win32 calls use `CreateFileA`.
- `new T(this)` in the CreateFile functions is the kernel's inline operator new (tmalloc + null test); placement new on
  tmalloc memory gives a different branch layout. Include TNewDelete.h, write `new T(this)` and `delete file` on failure
  (a virtual scalar-deleting-destructor call, so the virtual destructor is the last slot).
- Constructors of the file classes live in their own TUs (TNativeFileCtor.cpp, TNullFileCtor.cpp, TMemFileCtor.cpp,
  TISOFileCtor.cpp), otherwise ICC inlines them into CreateFile. TISOFile's empty destructor is out of line next to its ctor.
- Buffered Read (TNativeFile / TISOFile): the original ends `if (total != size) { if (!LoadBuffer(block)) return total; ...copy }
  return total;`. The reversed form `if (total == size) return total;` lets ICC reuse the loaded register and shortens the code by
  4 bytes. Same fix matched both functions.
- `min(a, b)` over two address-taken locals forces both into stack slots: the shared `Min(const T&, const T&)` template in
  TKernelMisc.h reproduces the original's `lea edx,[esp+4]` selection.
- Float members are zeroed with `= 0.0f` (immediate store); an int zero would be CSE'd into `xor reg` (TTimer +0x40).
- `return (flags & 4) != 0;` and `if (flags & 4) return true; return false;` generate different code: TTask flag accessors
  use the if/return form.
- Uploaded Src copies in the session container go stale: stage the device copy of a file before editing it, or earlier edits
  are dropped (round 369 lost ISO9660PVD and ~TRandom that way).
- Open: TScheduler::SetDebugSlowTime keeps 0.01f / 1.0f in a register and stores once (`mov eax,imm / jmp / store`); the plain
  `slow ? 0.01f : 1.0f` and an if/else both store the immediate in each branch. A named temporary matches but is an added
  construct, so it is not committed (the original probably went through a helper).


## PGUICore start, accessor-only classes (rounds 388-400, 2026-11-13)
- Accessor-only classes compile fine with offset-named placeholder bytes (`unsigned char m_unk00[0x10]`) for the unknown prefix; no vtable is needed when only non-virtual accessors are written. Derived layout classes only need the base header (TGUILayoutManager).
- A TNodeList<T> member needs T complete where the implicit destructor is instantiated: include the header of T in the class header (TGUIFont.h includes TGUITextureSection.h) or the TU fails with 'pointer to incomplete class'.
- Headers in Src\TKernelInterface (TKernelEmitter.h, TKernelThreads.h) are not on the include path of other DLL folders; only Src\include is shared.
- A commit of sources and request.txt in the same device_commit_files call can build the old files (r393/394 saw the stale TGUIWidgetAction header): commit the sources first, the request in a later call.
- An implicit dtor/ctor/operator= in a new exported class shows up as a DIFF in scoreall (TGUIFont ctor/dtor, PGUIDiscLayout dtor): the originals are user-written; do not chase them without the body.


## PGUICore, widget lists and menu classes (rounds 401-462, 2026-11-13)
- TNode/TNodeList offsets: for PGUIItemData/RowData/TGUIWidget the TNode sits at +4 (m_pList +4, next +8, prev +0xC); a list member at +X has its end sentinel at +X-4, head at +X+4, tail at +X+8, count at +X+0xC (`End()` is root-4 as a T*).
- Iterator construction order decides registers: declare begin first, then end, then the other iterator (`it(Begin); end(End); [other]`). Dual-list scans (FindItemWidget/FindWidgetItem) are `for (; a != aEnd && b != bEnd; ++a, ++b)`.
- Walking N siblings: a `for (i < n) ++it;` with the null-guarded Iterator matches (MenuTree::InvokeMenu); FindChildItem needs `while (index > 0 && it != end)`, the `for` form is a shrink-wrap DIFF.
- Style properties whose setter calls an out-of-line `SetListItemStyle(TGUIStyle*)` go into their own TU (PGUIListBoxStyles.cpp), otherwise ICC inlines the setter; Get_ uses `PPropertyValue(m_pStyle ? m_pStyle->GetName() : TPCString())`.
- Factory statics are decorated by access: the original `CreateObject` of an abstract PGUI class is `private static` (mangled `C`); `public` gives `S`, `protected` `K` and the symbol is not matched.
- Adding a TNodeList member to a class whose ctor/dtor are not written makes ICC emit implicit ctor/dtor that are then scored and FILED (MenuBar, MenuDialog dtors). Expect those open diffs; do not chase them.
- Header inline `SetState(mask, value)` is what the original inlined into PropagateState: moving it into PGUIItemData.h kept every other match.
- InsertTail inline: the original hoists both `lea` instructions before the first store (ListBox/TableBox AddItemImpl, MenuTreeItem::AddItem, DiscardButton, DiscardDialog): sched wall, same family.
- TGUIWidget vtable: slot 33 (+0x84) = Pack, slot 34 (+0x88) = Layout(-1,-1); TGUIWidget.h lacks slots 34+, so Layout/Paint/UpdateSelection-style functions are not written yet. A copy ctor + Clone needs TGUI_API TGUINew (dllimport).
- Growing a base member list shifts the placeholders of derived classes: re-check every derived m_unkXX offset comment after changing TGUIWidget.h.
- Tooling: commit sources first, then request.txt in a separate call, and always use a new staged file name per commit (the bridge can serve a cached same-named file).
- Overloaded virtuals take their vtable slots in REVERSE declaration order in ICC (TTextureResource::Create(const char*,...) = +0x3c, Create(void*,...) = +0x38 only when the const char* overload is declared first); check the vtable offset in the original caller before ordering overloads.
- Original `if (p) { if (p) p->Release(); p = 0; }` (second null test kept by ICC) = the DirectX sample SAFE_RELEASE macro followed by `p = 0`: TRenderD3DInterface::DestroyDisplay and both block DestroyHAL functions. Statement macro in d3d8min.h with an `// original macro:` comment.
- A small private or class-accessor function defined in the same TU is inlined by our ICC build even when the original calls it out of line (TMSWindow::Destroy -> GetHWND/Disable, CreateAcceleratorTableA -> DestroyAcceleratorTable); reordering the definitions did not change that. Family of open diffs, not a source error.
- Header inline accessor with `if (flags & X) return true; return false;` (TModel::IsLoaded) must be defined in the class body: the original inlines it into TModelD3D::Load (mov al,1 / xor al,al then cmp al,1).
- Friend access: TTextureResource lists TTextureFactory as friend; TTextureFactoryHAL needs its own `friend class` to call the protected Create(const char*, flags) (friendship is not inherited).
