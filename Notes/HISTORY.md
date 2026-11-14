# History - JPOG

The "Current state" section of CLAUDE.md as it was on 2026-11-12, kept whole when CLAUDE.md was shortened.
Newer sessions are in CLAUDE.md; move an entry here when CLAUDE.md has more than three.

## Current state (2026-10-29, TGuiInterface session, rounds 192-225) (archived 2026-11-12)
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

## Moved from CLAUDE.md on 2026-11-12
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


## Moved from CLAUDE.md on 2026-11-13
- **2026-11-10 (setup update).** TGFXFileInstanceObject.cpp: the shader accessors used raw offsets
  (`*(int*)((char*)this + 0x30)`), now declared members of TGFXInstanceShaderI (m_iTextureStagesState 0x30,
  m_unk34, m_fAlpha 0x38) - round-258 (TRenderInterface) was queued to confirm that Render still matches; check its
  result first. New rules: raw offset arithmetic, steering pragmas, `original macro:` evidence for boilerplate
  macros (the CreateObject / CreateObjectInPlace family is a candidate), notes through Notes\NOTES_INDEX.md,
  wall budget (section "Mismatch sessions"). Last build round: round-258.

## Archived 2026-11-13
- **2026-11-13 (TKernelInterface, TGuiInterface, PGUICore; rounds 361-400).** scoreall: TKernelInterface 1146 -> 1183 matched (52 open, 72 compiler-limited), TGuiInterface 629 -> 663 (TGUIInterface, TGUIFont, TGUIFormattedText, TGUIWidgetAction accessors), PGUICore 0 -> 59 (new Src\PGUICore: PGUIDiscLayout/OverlayLayout/StackLayout/GridLayout, PGUIItemData/MenuTreeItem/MenuTreeItemStyle, PGUIRowData accessors; PGUIAPI.h export macro, TGUILayoutManager::Alignment enum added). Kernel: file Read tails, TTask::Activate, TScheduler::Update, TKernelInterface::Update, the TFileLexerUTF8/16 helpers, TEmitter<Owner,Event>. TTimer::OnUpdate is filed compiler-limited (2/2); TScheduler::SetDebugSlowTime stays a DIFF on purpose (only a named temporary matches). scoreall numbers only; the anti-cheat has NOT been re-run. TKernelEmitter.h lives in Src\TKernelInterface, so TGuiInterface cannot include it yet (TGUIWidgetAction::Throw waits for that). Next step: PGUICore widget classes (PGUIListItem, PGUISliderBar, PGUIMenuTree margins), TDList for TGUIWidget lists. Last build round: round-400.

## Moved from CLAUDE.md on 2026-11-14
- **2026-11-12 (TGuiInterface, rounds 311-341).** scoreall: TGuiInterface 596 -> 629 matched (40 open, 22 compiler-limited, 466 not written);
  other DLLs unchanged. No placeholders renamed (no documentation round). Main levers: the covariant Clone return types (the mangled
  name returns the own class, so the five components, TextureSection, TextureAnimation and FontGlyph now count), TGUIDeserialisable
  Set/Get/ValidateProperty, TGUIWidget lookups (FindChildManager, FindIndexedChild, SetPositionCenter, HitTest, GetScreen, RequestFocus,
  NotifyFocusLost), TGUITextureAnimation ctors in their own TU (TGUITextureAnimationCtors.cpp: defining them next to CreateObject made
  ICC inline them there). New minimal TGUIScreen.h (m_sClass, ReleaseFocus, ChangeWidgetFocus) - its implicit ctor/dtor now show as open
  diffs. Parked (2/2): TGUIWidget::CanMove, FindNamedChild, RemoveFocus, TGUITextureAnimation::RemoveFrame. Filed: Val_width/height_property,
  Val_default_focus_property, TGUITextureSection::Assign, TGUIElement ctor. Anti-cheat NOT re-run: scoreall numbers only. Last build round: round-341.
  Next step: TGUIScreen (ReleaseFocus/ChangeWidgetFocus bodies, ctor/dtor), TGUIWidget slots 34-41 (RemoveWidget family), TDList-based
  StateSlave/Action lists, TSortedArray + the ordered-set statics, then PGUICore.dll.
