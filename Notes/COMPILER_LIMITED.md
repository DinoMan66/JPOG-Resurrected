# Functions skipped as compiler-limited (build 010525Z vs the original 020125Z)

These functions are written. They match the original's logic, but our ICC 5.0.1 build 010525Z
generates different code for reasons no source change has fixed. Re-test them when another
compiler is available (ICC 6.0 comparison builds, or build 020125Z if it turns up).

The patterns (see MATCHING_NOTES.md #23) are:
- **inline** — the original keeps small inline functions as calls; ours inlines them (no -Ob/-Qip option changes this)
- **shrink-wrap** — the original saves callee-saved registers in the prologue; ours saves them inside the branch that needs them
- **sched** — instruction order or register choice differs, with the same operations
- **dead-store** — the original keeps dead temporaries or stores
- **fp-const** — float constants are used as DWORD vs QWORD operands, 2*x is fmul vs fadd, or float-to-int conversion differs

## TRenderInterface.dll

| Function | Pattern | Notes |
|---|---|---|
| TAnimation::GetSequencePtr | sched | |
| ~TKeyframeLibraryInstance | sched | |
| TResource::IsValid | inline | IsCreated is kept as a call |
| TResource / TNullResource / TShader copy ctor | sched | movzx vs mov in the char[] copy |
| TResource::SetName | sched | |
| TAtmosphere::SetAtmHGg, InitVSConstants, CalculateScatteringConstants | fp-const | |
| TSun::ComputeAttenuation | fp-const | constants and slot order |
| TSun::SetTheta / Set | sched | static-guard block layout |
| TSun::SetBiasColour | fp-const | |
| TRenderAdapter::~TRenderAdapter | shrink-wrap | |
| TRenderContext::CullSphereToFrustum | sched | 1 byte |
| TRenderContext::GetWorldPlanes / GetWorldGuardPlanes | sched | induction-variable choice |
| TRenderContext ctor | sched / dead-store | |
| TRenderInterface ctor | sched / dead-store | vtable store position; the original keeps a dead TVector2 temp (the memset now matches) |
| TRenderInterface dtor | shrink-wrap | |
| TRenderInterface::CreateResource / CreateResourceInPlace | sched | the parent parameter is reloaded from the stack |
| TRenderInterface::FlushShadersRecurse | shrink-wrap | |
| TRenderInterface::MakeRGBA(float x4) | fp-const | the original truncates double to uint inline (shld/shr); ours uses fistp + fldcw |
| TRenderInterface::FindDevice, DumpStats | (re-testing) | GetModeList turned out to be TRenderAdapter.cpp's only function (non-inline): fixed in round 67 |
| TNodeTree<TResource>::Recurse (0xc840) | inline | the original calls the out-of-line TResource::Next/Child (0x7e30/0x7e40) |
| TRenderInterface::DestroyDyingResources, DestroyResourceTypeRecurse | padding | 3 bytes: a different encoding of the nop padding inside the loop |
| TMaterialLibrary::Create, ReadHeader, LoadMaterial, LoadTerrainMaterial | sched | the original duplicates the small `return false` epilogues; ours merges them |
| TMaterialLibrary::LoadMaterials, LoadTexture, LoadSkin/System/SpriteMaterial | sched | register allocation: the original keeps the flags local in a stack slot |
| TMaterialLibraryManager::LoadMaterialLibrary, TModel::CreateInstance | inline | the original calls the protected constructors out of line; ours inlines them |
| ~TMaterialLibraryManager | sched | null-checked list stepping / loop layout |
| TMaterial / TMesh / TShader copy ctors | sched | movzx vs mov in the inherited TResource name copy |
| TDBase::TKeyFrame::IsInTimeRange, IsInExclusiveTimeRange | sched | the original pops the x87 stack on each early exit and keeps two `return false` epilogues; ours merges them. 5 source forms tried (round 83) |
| TDBase::TKeySequence::DeleteData, TSequence::DeleteData | sched | the original saves registers with pushes and keeps RemoveHead's empty-list `return 0` inline; ours uses stack spills and an out-of-line block |
| TKeyframeLibraryManager::GetLibrary, DebugDump | dead-store | ours stores the End() iterator to two stack slots and rotates the loop; same family as FindTexture |
| TSkeleton::GetSequence(name), GetBone(name) | inline | the original calls GetSequence(int)/GetBone(int) out of line (same file) |

## Auto-filed by verdict.py

Filed after 2 real attempts with a difference of a compiler-limited kind (see Tools/triage_lib.py). Re-test when another compiler build is available.

| Module | Function | Address | Kind | First difference (ours / orig) | Filed |
|---|---|---|---|---|---|
| TRenderInterface.dll | TSkeletonInstance::RemoveAnimation | 0x47c0 | regalloc | `push   ebx` / `push   ebp` | 2026-10-28 |
| TRenderInterface.dll | TAnimation::SetTime | 0x5360 | regalloc | `push   esi` / `push   edi` | 2026-10-28 |
| TRenderInterface.dll | TAnimation::UpdateTime | 0x54c0 | regalloc | `push   edi` / `push   esi` | 2026-10-28 |
| TRenderInterface.dll | TDImp::ComposeHierarchy | 0x156f0 | shrink-wrap | `push   esi` / `sub    esp,0xc` | 2026-10-28 |
| TRenderInterface.dll | TDImp::ReorderAllKeySeqs | 0x15730 | shrink-wrap | `push   edi` / `sub    esp,0x6c` | 2026-10-28 |
| TRenderInterface.dll | TDImp::MarkMeshSet | 0x16b70 | regalloc | `mov    esi,ecx` / `mov    edi,ecx` | 2026-10-28 |
| TRenderInterface.dll | TBone::ReorderKeySeqs | 0x17bb0 | shrink-wrap | `push   edi` / `sub    esp,0x24` | 2026-10-28 |

**Resolved 2026-10-28 (rounds 85-88):** TMaterialLibraryManager::GetMaterial and TTextureFactory::FindTexture were
not the compiler: the iterators' comparison operators take the iterator BY VALUE (TNodeList.h / TQList.h), and
GetMaterial / PProperties::GetProperty cache `End()` in a local. Also fixed: TKeySequence::GenerateExportCloseKey,
PProperties::PutProperty x2 and PutPropertyUnique (TQList::InsertTail through the node). The 7 functions filed
above on 2026-10-28 were counted as a second attempt because the header change altered their code.
| TKernelInterface.dll | TMatrix44::Add | 0x1bcf0 | regalloc | `push   edi` / `push   ebx` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::Subtract | 0x1bd40 | regalloc | `push   edi` / `push   ebx` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::IsEqual | 0x1bf80 | regalloc | `push   edi` / `push   ebx` | 2026-10-28 |
| TKernelInterface.dll | TBitArray::Create | 0x8e80 | regalloc | `push   esi` / `push   ebp` | 2026-10-28 |
| TKernelInterface.dll | TCString::MakeLower | 0xa880 | regalloc | `push   ebx` / `push   ebp` | 2026-10-28 |
| TKernelInterface.dll | TCString::MakeUpper | 0xa8a0 | regalloc | `push   ebx` / `push   ebp` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::TransformVector | 0x1c460 | regalloc | `mov    edx,dword ptr [esp+0x4]` / `mov    ecx,dword ptr [esp+0x4]` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::TransformVector | 0x1c4d0 | regalloc | `mov    eax,dword ptr [esp+0x4]` / `mov    ecx,dword ptr [esp+0x4]` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::RotateVector | 0x1c570 | regalloc | `mov    edx,dword ptr [esp+0x4]` / `mov    ecx,dword ptr [esp+0x4]` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::RotateVector | 0x1c5d0 | sched | `fxch   st(1)` / `mov    edx,dword ptr [ecx+0xc]` | 2026-10-28 |
| TKernelInterface.dll | TCString::Concat | 0x9c60 | regalloc | `mov    edi,dword ptr [esp+0x24]` / `mov    ebp,dword ptr [esp+0x24]` | 2026-10-28 |
| TKernelInterface.dll | TCString::Concat | 0x9da0 | regalloc | `mov    edi,dword ptr [esp+0x24]` / `mov    ebp,dword ptr [esp+0x24]` | 2026-10-28 |
| TKernelInterface.dll | TCString::FindReverse | 0x9f20 | regalloc | `push   esi` / `push   edi` | 2026-10-28 |
| TKernelInterface.dll | TWString::Concat | 0x287e0 | regalloc | `mov    ebx,dword ptr [esi+0x4]` / `mov    edi,dword ptr [esi+0x4]` | 2026-10-28 |
| TKernelInterface.dll | TWString::Concat | 0x28880 | regalloc | `mov    ebx,dword ptr [esi+0x4]` / `mov    edi,dword ptr [esi+0x4]` | 2026-10-28 |
| TKernelInterface.dll | TWString::FindReverse | 0x28a00 | regalloc | `push   esi` / `push   edi` | 2026-10-28 |
| TKernelInterface.dll | TMath::PointVsPlane3D | 0x1a510 | regalloc | `push   ebp` / `push   ebx` | 2026-10-28 |
| TKernelInterface.dll | TMath::LineVsLine2D | 0x19fe0 | regalloc | `push   ebx` / `push   ebp` | 2026-10-28 |
| TKernelInterface.dll | TMath::ClosestPointOnLine2D | 0x1a330 | regalloc | `mov    edx,dword ptr [esp+0x24]` / `mov    eax,dword ptr [esp+0x24]` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::RotateX | 0x1c210 | regalloc | `fld    dword ptr [esp+0x4]` / `fld    dword ptr [edi+0x10]` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::RotateY | 0x1c2b0 | regalloc | `push   esi` / `push   edi` | 2026-10-28 |
| TKernelInterface.dll | TMatrix44::RotateZ | 0x1c340 | regalloc | `fld    dword ptr [esp+0x4]` / `fld    dword ptr [edi+0x10]` | 2026-10-28 |
| TKernelInterface.dll | THPTimer::Update | 0x12d80 | sched | `mov    edx,dword ptr [ebx+0x14]` / `fild   qword ptr [ebx]` | 2026-10-29 |
| TKernelInterface.dll | TQuaternion::RotateAroundAxis | 0x23840 | regalloc | `push   ebp` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TMath::Pow | 0x1acf0 | shrink-wrap | `sub    esp,0x14` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TMath::Log | 0x1ad40 | shrink-wrap | `sub    esp,0xc` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TMath::Exp | 0x1ad90 | shrink-wrap | `sub    esp,0xc` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TMath::ATan | 0x1ade0 | shrink-wrap | `sub    esp,0xc` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TMath::ACos | 0x1ae30 | shrink-wrap | `sub    esp,0xc` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TMath::ASin | 0x1ae80 | shrink-wrap | `sub    esp,0xc` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TNativeFile::GetSize | 0x6800 | regalloc | `push   ebp` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TFreeList::ctor | 0x12be0 | regalloc | `push   ebp` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TRandom::GetInt | 0x24a00 | regalloc | `push   edi` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TRandom::GetInt | 0x24a40 | regalloc | `push   esi` / `push   ebp` | 2026-10-29 |
| TKernelInterface.dll | TSumOfMinterms::ctor | 0x1f160 | shrink-wrap | `push   ebp` / `sub    esp,0xc` | 2026-10-29 |
| PPropertyParser.dll | PPropertyValueArray::ctor | 0x6f20 | shrink-wrap | `push   esi` / `sub    esp,0xc` | 2026-10-29 |
| TGuiInterface.dll | TGUIComponentInfo::dtor | 0x24ba0 | regalloc | `push   ebp` / `push   edi` | 2026-10-29 |
| TGuiInterface.dll | TGUIComponentInfo::AddElementName | 0x261b0 | regalloc | `mov    ebp,ecx` / `mov    esi,ecx` | 2026-10-29 |
| TGuiInterface.dll | TGUIDisplayContext::PushClip | 0xa100 | regalloc | `mov    ebp,ecx` / `mov    esi,ecx` | 2026-10-29 |
| TKernelInterface.dll | TMatrix44::LookAtTarget | 0x1c3d0 | sched | `mov    dword ptr [ebp+0x0],eax` / `fld    dword ptr [ebp+0x20]` | 2026-10-29 |
| TKernelInterface.dll | TMath::DistancePointToLineSq | 0x1a3a0 | sched | `mov    eax,dword ptr [eax+0x4]` / `mov    dword ptr [esp+0x8],edx` | 2026-10-29 |
| TKernelInterface.dll | TQuaternion::RotateVector | 0x23b20 | regalloc | `push   edi` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TVector3::SetVectorProjection | 0x274e0 | regalloc | `push   esi` / `push   edi` | 2026-10-29 |
| TKernelInterface.dll | TGenericPriList::operator= | 0x7540 | regalloc | `mov    edx,dword ptr [esp+0x4]` / `mov    ecx,dword ptr [esp+0x4]` | 2026-10-29 |
| TKernelInterface.dll | TMemFile::Read | 0x1d610 | regalloc | `jmp    0x33` / `jmp    0x37` | 2026-10-29 |
| TKernelInterface.dll | TGenericPool::ResetBlock | 0x219f0 | regalloc | `push   ebp` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TAABox::ComparePlane | 0x8210 | sched | `fld    dword ptr ds:0x4` / `fld    qword ptr [esp+0x10]` | 2026-10-29 |
| TKernelInterface.dll | TMemFile::Seek | 0x1d650 | regalloc | `push   edi` / `push   esi` | 2026-10-29 |
| TKernelInterface.dll | TRandom::GetFloatMinMax | 0x24980 | regalloc | `fxch   st(2)` / `fxch   st(1)` | 2026-10-29 |
| TKernelInterface.dll | TMemory::dtor | 0x1ec30 | regalloc | `push   ebx` / `push   edi` | 2026-10-29 |
| TKernelInterface.dll | TVector2::Rotate | 0x26900 | regalloc | `fld    dword ptr [esp]` / `fld    dword ptr [ebp+0x0]` | 2026-10-29 |
| TKernelInterface.dll | TVector3::RotateX | 0x27200 | sched | `fld    dword ptr [esp]` / `fld    dword ptr [ebp+0x4]` | 2026-10-29 |
| TKernelInterface.dll | TVector3::RotateY | 0x27250 | regalloc | `fld    dword ptr [esp]` / `fld    dword ptr [ebp+0x0]` | 2026-10-29 |
| TKernelInterface.dll | TVector4::RotateX | 0x28010 | sched | `fld    dword ptr [esp]` / `fld    dword ptr [ebp+0x4]` | 2026-10-29 |
| TKernelInterface.dll | TVector4::RotateY | 0x28060 | regalloc | `fld    dword ptr [esp]` / `fld    dword ptr [ebp+0x0]` | 2026-10-29 |
| TRenderInterface.dll | TSkeleton::CreateInstance | 0x61f0 | regalloc | `movzx  edi,word ptr [ebp+0x6]` / `movzx  esi,word ptr [ebp+0x6]` | 2026-10-29 |
| TGuiInterface.dll | TGUISawtoothFunction::ComputeNormalised | 0x6fe0 | fp | `fld    qword ptr ds:0x70` / `fld    dword ptr ds:0x100490b8` | 2026-10-29 |
| TGuiInterface.dll | TGUIStyleState::ctor | 0x15bb0 | shrink-wrap | `push   ebx` / `sub    esp,0x10` | 2026-10-29 |
| TGuiInterface.dll | TGUIElement::Assign | 0x27ea0 | regalloc | `push   esi` / `push   edi` | 2026-10-29 |
| TKernelInterface.dll | TVector3::SetUnitVectorProjection | 0x27490 | regalloc | `push   esi` / `push   edi` | 2026-10-29 |
| TGuiInterface.dll | TGUIPropertySpec::operator= | 0x129a0 | regalloc | `mov    edi,ecx` / `mov    esi,ecx` | 2026-10-30 |
| TGuiInterface.dll | TGUIWidgetInfo::dtor | 0x1b0c0 | regalloc | `push   ebx` / `push   esi` | 2026-10-30 |
| TGuiInterface.dll | TGUIWidget::DeinitialiseStatic | 0x1c970 | regalloc | `push   ebx` / `push   ebp` | 2026-10-30 |
| TGuiInterface.dll | TGUIWindow::DeinitialiseStatic | 0x22300 | regalloc | `push   ebx` / `push   edi` | 2026-10-30 |
| PPropertyParser.dll | PPropertyReader::GetValue | 0x4e00 | regalloc | `mov    dword ptr [esi+0x4],edx` / `mov    dword ptr [esi+0x8],eax` | 2026-10-30 |
| TKernelInterface.dll | TGenericFifo::Push | 0x7be0 | regalloc | `push   ebp` / `push   esi` | 2026-11-03 |
| TKernelInterface.dll | TGenericFifo::Pop | 0x7c70 | regalloc | `push   ebp` / `push   esi` | 2026-11-03 |
| PPropertyParser.dll | PPropertyWriter::Put | 0x8890 | regalloc | `push   esi` / `push   edi` | 2026-11-03 |
| TKernelInterface.dll | TRandom::Isaac | 0x24370 | regalloc | `mov    ebp,ecx` / `mov    esi,ecx` | 2026-11-03 |
