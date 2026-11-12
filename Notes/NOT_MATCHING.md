# JPOG: functions that still do not match (2026-11-03, rounds 251-257)

Compiler in the VM: ICC 5.0.1 build 010525Z; the game was built with 020125Z. Categories come from verdict.py (first
difference). Re-examined after the Zoo Tycoon findings (rounds 254-257): four functions filed as compiler-limited were
source differences and now match (TFileManager::UnmountFileSystem, TThreadManager::RemoveThread, TGUIIconComponent::
CreateObject / CreateObjectInPlace - MATCHING_NOTES 'Re-examination').

Marks in the table:
- **inl**: the original calls a small non-inline function of the same file that our compiler inlines. This is the
  compiler-build difference of MATCHING_NOTES #23. Only moving that function into another file would hide it from
  our compiler.
- Other notes are per function.

Known source-side work: PProperties::dtor (TQList form), the unwritten GUI InitialiseStatic property sets.
Total: 272 functions. Progress numbers: Notes\VERIFIED_PROGRESS.md only.

## regalloc (141) - same instructions, different registers

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | ??8PPropertyName@@QBE_NABV0@@Z | 0x2dc0 |  |
| PPropertyParser | ??9PPropertyName@@QBE_NABV0@@Z | 0x2e10 |  |
| PPropertyParser | PProperties::GetRequiredProperty | 0x15f0 |  |
| PPropertyParser | PPropertyBlock::dtor | 0x2b80 |  |
| PPropertyParser | PPropertyReader::AddDefinitionBlock | 0x3570 |  |
| PPropertyParser | PPropertyReader::GetValue | 0x4e00 |  |
| PPropertyParser | PPropertyReader::Load | 0x38c0 |  |
| PPropertyParser | PPropertyReader::LoadPropertyName | 0x44f0 |  |
| PPropertyParser | PPropertyReader::Token2Value | 0x4af0 |  |
| PPropertyParser | PPropertyReader::ctor | 0x32b0 |  |
| PPropertyParser | PPropertyValueArray::GetTVector2 | 0x6fe0 |  |
| PPropertyParser | PPropertyValueArray::ctor | 0x26e0 |  |
| PPropertyParser | PPropertyValueArray::ctor | 0x27a0 |  |
| PPropertyParser | PPropertyWriter::AddDefinitionBlock | 0x9330 |  |
| PPropertyParser | PPropertyWriter::Put | 0x8500 |  |
| PPropertyParser | PPropertyWriter::Put | 0x8890 |  |
| PPropertyParser | PPropertyWriter::Save | 0x81a0 |  |
| TGuiInterface | TGUIComponentInfo::AddElementName | 0x261b0 |  |
| TGuiInterface | TGUIComponentInfo::dtor | 0x24ba0 |  |
| TGuiInterface | TGUIConstantFunction::ctor | 0x71e0 |  |
| TGuiInterface | TGUIDisplayContext::PushClip | 0xa100 |  |
| TGuiInterface | TGUIElement::Assign | 0x27ea0 |  |
| TGuiInterface | TGUIElement::ChangeType | 0x26c70 |  |
| TGuiInterface | TGUIFunction::ctor | 0x72d0 |  |
| TGuiInterface | TGUILayoutManager::ctor | 0x12740 |  |
| TGuiInterface | TGUIPropertySpec::ctor | 0x12cf0 |  |
| TGuiInterface | TGUIPropertySpec::operator= | 0x129a0 |  |
| TGuiInterface | TGUISawtoothFunction::ctor | 0x6fb0 |  |
| TGuiInterface | TGUISineFunction::ctor | 0x70d0 |  |
| TGuiInterface | TGUIStyleState::dtor | 0x6990 |  |
| TGuiInterface | TGUIWidget::DeinitialiseStatic | 0x1c970 |  |
| TGuiInterface | TGUIWindow::DeinitialiseStatic | 0x22300 |  |
| TInputDXInterface | TInputDXInterface::EnumerateDeviceCallback | 0x3890 | inl |
| TInputInterface | ?SetCapacity@?$TArray@URepeatInfo@TInputDevice@Toshi@@@Toshi@@QAEXH@Z | 0x17a0 |  |
| TInputInterface | TInputDevice::IsLatched | 0x14e0 |  |
| TInputInterface | TInputDevice::Latch | 0x12a0 |  |
| TInputInterface | TInputDevice::ProcessRepeats | 0x1560 | inl |
| TInputInterface | TInputDevice::StartRepeat | 0x1100 |  |
| TInputInterface | TInputDevice::StopRepeat | 0x11f0 |  |
| TInputInterface | TInputDevice::Unlatch | 0x1450 |  |
| TKernelInterface | TCString::Concat | 0x9c60 |  |
| TKernelInterface | TCString::Concat | 0x9da0 |  |
| TKernelInterface | TCString::FindReverse | 0x9f20 |  |
| TKernelInterface | TCString::MakeLower | 0xa880 |  |
| TKernelInterface | TCString::MakeUpper | 0xa8a0 |  |
| TKernelInterface | TFreeList::ctor | 0x12be0 |  |
| TKernelInterface | TGenericFifo::Pop | 0x7c70 |  |
| TKernelInterface | TGenericFifo::Push | 0x7be0 |  |
| TKernelInterface | TGenericNodeList::IsEmpty | 0x1fa50 |  |
| TKernelInterface | TGenericPool::AllocBlock | 0x21990 |  |
| TKernelInterface | TGenericPool::ResetBlock | 0x219f0 |  |
| TKernelInterface | TGenericPriList::operator= | 0x7540 |  |
| TKernelInterface | TMatrix44::Add | 0x1bcf0 |  |
| TKernelInterface | TMatrix44::IsEqual | 0x1bf80 |  |
| TKernelInterface | TMatrix44::RotateVector | 0x1c570 |  |
| TKernelInterface | TMatrix44::RotateX | 0x1c210 |  |
| TKernelInterface | TMatrix44::RotateY | 0x1c2b0 |  |
| TKernelInterface | TMatrix44::RotateZ | 0x1c340 |  |
| TKernelInterface | TMatrix44::Subtract | 0x1bd40 |  |
| TKernelInterface | TMatrix44::TransformVector | 0x1c460 |  |
| TKernelInterface | TMatrix44::TransformVector | 0x1c4d0 |  |
| TKernelInterface | TMemFile::Read | 0x1d610 |  |
| TKernelInterface | TMemFile::Seek | 0x1d650 |  |
| TKernelInterface | TMemory::dtor | 0x1ec30 | inl |
| TKernelInterface | TNativeFile::GetSize | 0x6800 |  |
| TKernelInterface | TObject::IsExactly | 0x201e0 |  |
| TKernelInterface | TPile::RawAlloc | 0x21790 |  |
| TKernelInterface | TPile::Reset | 0x21750 |  |
| TKernelInterface | TQuaternion::RotateAroundAxis | 0x23840 |  |
| TKernelInterface | TQuaternion::RotateVector | 0x23b20 |  |
| TKernelInterface | TRandom::GetFloatMinMax | 0x24980 |  |
| TKernelInterface | TRandom::GetInt | 0x24a00 | original contains inline assembly (left as a mismatch) |
| TKernelInterface | TRandom::GetInt | 0x24a40 | original contains inline assembly (left as a mismatch) |
| TKernelInterface | TRandom::Isaac | 0x24370 | call set and length now match; register choice left |
| TKernelInterface | TRandom::RandRaw | 0x24920 |  |
| TKernelInterface | TVector2::Normalise | 0x26810 |  |
| TKernelInterface | TVector2::Rotate | 0x26900 |  |
| TKernelInterface | TVector3::Normalise | 0x26f60 |  |
| TKernelInterface | TVector3::RotateY | 0x27250 |  |
| TKernelInterface | TVector3::SetUnitVectorProjection | 0x27490 |  |
| TKernelInterface | TVector3::SetVectorProjection | 0x274e0 |  |
| TKernelInterface | TVector4::Normalise | 0x27e70 |  |
| TKernelInterface | TVector4::RotateY | 0x28060 |  |
| TKernelInterface | TWString::Concat | 0x287e0 |  |
| TKernelInterface | TWString::Concat | 0x28880 |  |
| TKernelInterface | TWString::FindReverse | 0x28a00 |  |
| TRenderInterface | ResourceName::Compare | 0x8b90 |  |
| TRenderInterface | ResourceName::Compare | 0x8bd0 |  |
| TRenderInterface | TAnimation::ChangeToManaged | 0x5400 |  |
| TRenderInterface | TAnimation::SetTime | 0x5360 |  |
| TRenderInterface | TAnimation::UpdateTime | 0x54c0 |  |
| TRenderInterface | TAtmosphere::CalculateScatteringConstants | 0x18790 |  |
| TRenderInterface | TBone::ctor | 0x8d70 |  |
| TRenderInterface | TCameraViewportHandler::GetRenderer | 0xeb30 | inl |
| TRenderInterface | TDImp::ImportKeySequence | 0x16000 |  |
| TRenderInterface | TDImp::MarkMeshSet | 0x16b70 |  |
| TRenderInterface | TKeySequence::dtor | 0x13d30 |  |
| TRenderInterface | TKeyframeLibrary::Create | 0x55e0 |  |
| TRenderInterface | TMaterial::ctor | 0x6b20 |  |
| TRenderInterface | TMaterialLibrary::Create | 0xcf10 |  |
| TRenderInterface | TMaterialLibrary::LoadMaterial | 0xd340 |  |
| TRenderInterface | TMaterialLibrary::LoadMaterials | 0xd250 |  |
| TRenderInterface | TMesh::ctor | 0x6a70 |  |
| TRenderInterface | TNullResource::ctor | 0x7cf0 |  |
| TRenderInterface | TRenderAdapter::dtor | 0x7c60 |  |
| TRenderInterface | TRenderContext::CullSphereToFrustum | 0xa6b0 |  |
| TRenderInterface | TRenderContext::GetGuardPlanes | 0xa360 |  |
| TRenderInterface | TRenderContext::GetViewPlanes | 0xa250 |  |
| TRenderInterface | TRenderContext::GetWorldGuardPlanes | 0xa1d0 |  |
| TRenderInterface | TRenderContext::GetWorldPlanes | 0xa150 |  |
| TRenderInterface | TRenderInterface::CreateResource | 0xb7b0 |  |
| TRenderInterface | TRenderInterface::CreateResourceInPlace | 0xb8d0 |  |
| TRenderInterface | TRenderInterface::DestroyDyingResources | 0xbfc0 |  |
| TRenderInterface | TRenderInterface::DestroyResourceTypeRecurse | 0xc1f0 | inl |
| TRenderInterface | TRenderInterface::FindResource | 0xbb70 |  |
| TRenderInterface | TRenderInterface::SetAsLastChild | 0xba00 |  |
| TRenderInterface | TRenderInterface::dtor | 0xae30 |  |
| TRenderInterface | TResource::SetName | 0x12c10 |  |
| TRenderInterface | TResource::ctor | 0x7d90 |  |
| TRenderInterface | TSequence::dtor | 0x13be0 |  |
| TRenderInterface | TShader::ctor | 0x6c40 |  |
| TRenderInterface | TSkeleton::CreateInstance | 0x61f0 |  |
| TRenderInterface | TSkeleton::GetBone | 0x80f0 | inl |
| TRenderInterface | TSkeleton::GetBoneID | 0x62e0 |  |
| TRenderInterface | TSkeleton::GetSequenceID | 0x63a0 |  |
| TRenderInterface | TSkeleton::dtor | 0x17f20 |  |
| TRenderInterface | TSkeletonInstance::GetBoneTransformCurrent | 0x5230 |  |
| TRenderInterface | TSkeletonInstance::IsAnimating | 0x48a0 |  |
| TRenderInterface | TSkeletonInstance::RemoveAnimation | 0x47c0 |  |
| TRenderInterface | TSkeletonInstance::UpdateTime | 0x49c0 |  |
| TRenderInterface | TSkinMesh::DeleteResources | 0x17690 |  |
| TRenderInterface | TSkinMesh::dtor | 0x180d0 | inl |
| TRenderInterface | TSun::Set | 0x18c60 |  |
| TRenderInterface | TSun::SetBiasColour | 0x18d40 |  |
| TRenderInterface | TSun::SetTheta | 0x18b60 |  |
| TRenderInterface | TTextureFactory::Dump | 0xdf10 |  |
| TRenderInterface | TTransformObject::GetLocalMatrix | 0x11db0 | inl |
| TRenderInterface | TTransformObject::Push | 0x11ac0 |  |
| TRenderInterface | TTransformObject::ctor | 0x119e0 |  |
| TRenderInterface | TViewport::DeleteHandlers | 0x129f0 |  |
| TRenderInterface | TViewport::dtor | 0x12250 |  |

## shrink-wrap (33) - callee-saved registers saved at a different point (the original often spills them into its frame)

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | PPropertyValueArray::ctor | 0x6f20 |  |
| TGuiInterface | TGUIStyle::InitialiseStatic | 0x15da0 | inl |
| TGuiInterface | TGUIStyleRootComponent::dtor | 0x6820 |  |
| TGuiInterface | TGUIStyleState::AddComponent | 0x6a10 |  |
| TGuiInterface | TGUIStyleState::ctor | 0x15bb0 |  |
| TGuiInterface | TGUIWidget::InitialiseStatic | 0x1b510 | inl |
| TGuiInterface | TGUIWindow::InitialiseStatic | 0x21660 | inl |
| TKernelInterface | TMath::ACos | 0x1ae30 |  |
| TKernelInterface | TMath::ASin | 0x1ae80 |  |
| TKernelInterface | TMath::ATan | 0x1ade0 |  |
| TKernelInterface | TMath::Exp | 0x1ad90 |  |
| TKernelInterface | TMath::Log | 0x1ad40 |  |
| TKernelInterface | TMath::Pow | 0x1acf0 |  |
| TKernelInterface | TSumOfMinterms::ctor | 0x1f160 | inl |
| TRenderInterface | TAnimation::GetSequencePtr | 0x8740 | inl |
| TRenderInterface | TAtmosphere::InitVSConstants | 0x18a50 |  |
| TRenderInterface | TBone::ReorderKeySeqs | 0x17bb0 |  |
| TRenderInterface | TDImp::ComposeHierarchy | 0x156f0 |  |
| TRenderInterface | TDImp::ReorderAllKeySeqs | 0x15730 |  |
| TRenderInterface | TDImp::dtor | 0x142f0 |  |
| TRenderInterface | TKeySequence::DeleteData | 0x13a50 |  |
| TRenderInterface | TKeyframeLibraryInstance::dtor | 0x68f0 | inl |
| TRenderInterface | TKeyframeLibraryManager::DebugDump | 0x58e0 | inl |
| TRenderInterface | TMaterialLibraryManager::dtor | 0xdab0 |  |
| TRenderInterface | TRenderInterface::FindDevice | 0xb440 |  |
| TRenderInterface | TRenderInterface::FindOrphanedResource | 0xbc30 |  |
| TRenderInterface | TRenderInterface::FlushShadersRecurse | 0xc190 |  |
| TRenderInterface | TRenderInterface::MakeRGBA | 0x7110 |  |
| TRenderInterface | TResource::IsValid | 0x12f20 | inl |
| TRenderInterface | TSequence::DeleteData | 0x13ab0 |  |
| TRenderInterface | TSkeleton::DeleteResources | 0x17ec0 |  |
| TRenderInterface | TSkeleton::GetSequence | 0x80b0 | inl |
| TRenderInterface | TViewport::AddHandler | 0x12a70 |  |

## sched (18) - same instructions, different order

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | PPropertyReader::Open | 0x3380 |  |
| PPropertyParser | PPropertyReader::Open | 0x3480 |  |
| TKernelInterface | TAABox::ComparePlane | 0x8210 |  |
| TKernelInterface | TGenericFifo::Create | 0x7b40 |  |
| TKernelInterface | THPTimer::Update | 0x12d80 |  |
| TKernelInterface | TMath::ClosestPointOnLine2D | 0x1a330 |  |
| TKernelInterface | TMath::DistancePointToLineSq | 0x1a3a0 |  |
| TKernelInterface | TMath::LineVsLine2D | 0x19fe0 |  |
| TKernelInterface | TMath::PointVsPlane3D | 0x1a510 |  |
| TKernelInterface | TMatrix44::LookAtTarget | 0x1c3d0 |  |
| TKernelInterface | TMatrix44::RotateVector | 0x1c5d0 |  |
| TKernelInterface | TSumOfMinterms::ctor | 0x1f1f0 | inl |
| TKernelInterface | TSumOfMinterms::ctor | 0x1f260 | inl |
| TKernelInterface | TVector3::RotateX | 0x27200 |  |
| TKernelInterface | TVector4::RotateX | 0x28010 |  |
| TRenderInterface | TLightingNode::Render | 0x103d0 | inl |
| TRenderInterface | TScene::Update | 0x10a10 |  |
| TRenderInterface | TTerrainObject::Render | 0x116a0 | inl |

## fp (5) - x87 code generation

| DLL | Function | RVA | Note |
|---|---|---|---|
| TGuiInterface | TGUIFunction::Compute | 0x7300 |  |
| TGuiInterface | TGUISawtoothFunction::ComputeNormalised | 0x6fe0 |  |
| TKernelInterface | TRandom::GetFloatMinRange | 0x24950 |  |
| TRenderInterface | TAtmosphere::SetAtmHGg | 0x186f0 |  |
| TRenderInterface | TCameraViewportHandler::OnBeginRenderEvent | 0xeb60 |  |

## branch (45) - block layout / branch sense, loop inversion, tail merging

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | ??8PPropertyValue@@QBE_NPBD@Z | 0x62d0 |  |
| PPropertyParser | ??8PPropertyValue@@QBE_NPBG@Z | 0x6320 |  |
| PPropertyParser | PProperties::GetRequiredProperty | 0x1520 |  |
| PPropertyParser | PProperties::GetRequiredProperty | 0x1580 |  |
| PPropertyParser | PPropertyValue::IsEmpty | 0x6570 |  |
| PPropertyParser | PPropertyWriter::Put | 0x8780 |  |
| PPropertyParser | PPropertyWriter::Put | 0x9270 |  |
| PPropertyParser | PPropertyWriter::PutPropertyBlock | 0x8340 |  |
| PPropertyParser | PPropertyWriter::PutPropertyName | 0x8220 |  |
| PPropertyParser | PPropertyWriter::PutToken | 0x8bf0 |  |
| PPropertyParser | PPropertyWriter::string_needs_quotes | 0x8ef0 |  |
| TGuiInterface | TGUIElement::IsDefined | 0x27490 |  |
| TGuiInterface | TGUILayoutManager::DeinitialiseStatic | 0x12580 | inl |
| TGuiInterface | TGUIPropertySpec::ctor | 0x12bb0 |  |
| TGuiInterface | TGUIStyle::DeinitialiseStatic | 0x16e80 |  |
| TInputDXInterface | TInputDXDeviceController::GetAxisInt | 0x14b0 |  |
| TInputDXInterface | TInputDXDeviceKeyboard::EnumObjectCallback | 0x2a60 | inl |
| TInputDXInterface | TInputDXDeviceMouse::ProcessEvents | 0x3040 |  |
| TKernelInterface | TBitArray::Create | 0x8e80 |  |
| TKernelInterface | TMemory::GetMemNodeFromAddress | 0x1eb80 |  |
| TKernelInterface | TQuaternion::Lerp | 0x23a80 |  |
| TKernelInterface | TSphere::ComparePlane | 0x25620 |  |
| TKernelInterface | TThreadManager::FindThread | 0x7e50 | inl |
| TKernelInterface | TVector3::IsReasonable | 0x27020 |  |
| TKernelInterface | TWString::Copy | 0x285c0 |  |
| TRenderInterface | ResourceName::Compare | 0x8c20 |  |
| TRenderInterface | TDImp::BuildImpParentChildHierarchy | 0x14b40 |  |
| TRenderInterface | TDImp::ImportKey | 0x16720 |  |
| TRenderInterface | TDImp::ImportSequence | 0x15ca0 |  |
| TRenderInterface | TDImpMaterial::FileRead | 0x16fa0 |  |
| TRenderInterface | TKeyFrame::IsInExclusiveTimeRange | 0x13dc0 |  |
| TRenderInterface | TKeyFrame::IsInTimeRange | 0x13df0 |  |
| TRenderInterface | TKeySequence::GenerateCloseKey | 0x136a0 |  |
| TRenderInterface | TMaterialLibrary::LoadSkinMaterial | 0xd410 |  |
| TRenderInterface | TMaterialLibrary::LoadSpriteMaterial | 0xd7a0 |  |
| TRenderInterface | TMaterialLibrary::LoadTerrainMaterial | 0xd550 |  |
| TRenderInterface | TMaterialLibrary::LoadTexture | 0xd170 |  |
| TRenderInterface | TMaterialLibrary::ReadHeader | 0xd090 |  |
| TRenderInterface | TModel::CreateInstance | 0x9670 | inl |
| TRenderInterface | TRenderContext::GetWorldGuardPlanes | 0xa550 |  |
| TRenderInterface | TRenderContext::GetWorldPlanes | 0xa470 |  |
| TRenderInterface | TRenderInterface::DeleteResourceAtomic | 0xc120 |  |
| TRenderInterface | TRenderInterface::MakeDepthStencilFormat | 0xb650 |  |
| TRenderInterface | TResource::SetParent | 0x12e20 |  |
| TRenderInterface | TSubMesh::FileRead | 0x17270 |  |

## stack (14) - stack frame size

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | PPropertyReader::Load | 0x3680 |  |
| PPropertyParser | PPropertyReader::LoadProperty | 0x3b00 |  |
| PPropertyParser | PPropertyValueArray::ctor | 0x2710 |  |
| PPropertyParser | PPropertyWriter::Put | 0x8ae0 |  |
| TGuiInterface | TGUIHorizontalTripletComponent::GetPreferredSize | 0x29750 |  |
| TInputInterface | TInputDeviceController::UpdateVirtualButtons | 0x1c90 |  |
| TRenderInterface | TBone::ComputeManualAndHook | 0x177d0 |  |
| TRenderInterface | TDImp::CollapseSequences | 0x15a50 |  |
| TRenderInterface | TGFXFileInstanceObject::Render | 0xf940 |  |
| TRenderInterface | TKeyframeLibraryManager::GetLibrary | 0x5850 |  |
| TRenderInterface | TRenderContext::ctor | 0x9c90 |  |
| TRenderInterface | TRenderInterface::DumpStats | 0xb030 |  |
| TRenderInterface | TRenderInterface::ctor | 0xab70 |  |
| TRenderInterface | TSun::ComputeAttenuation | 0x18da0 | inl |

## source (16) - flagged as source; on inspection a code-generation difference or unfinished function

| DLL | Function | RVA | Note |
|---|---|---|---|
| PPropertyParser | PProperties::FindProperty | 0x1740 |  |
| PPropertyParser | PProperties::PutPropertyUnique | 0x1390 | inl |
| PPropertyParser | PProperties::Sort | 0x17a0 |  |
| PPropertyParser | PProperties::dtor | 0x1100 |  |
| TGuiInterface | TGUIIconComponent::GetPreferredSize | 0x2a070 |  |
| TGuiInterface | TGUIWidget::GetInteriorHeight | 0x1de70 |  |
| TGuiInterface | TGUIWidget::GetInteriorWidth | 0x1de50 |  |
| TInputInterface | TInputInterface::dtor | 0x2840 |  |
| TKernelInterface | ??HTSumOfMinterms@Toshi@@QAEAAV01@ABVTMinterm@1@@Z | 0x1f0e0 |  |
| TKernelInterface | TMatrix44::AsBasisVector3 | 0x1d000 |  |
| TKernelInterface | TMatrix44::AsBasisVector3 | 0x1d010 |  |
| TKernelInterface | TMatrix44::AsBasisVector4 | 0x1cf80 |  |
| TKernelInterface | TMatrix44::AsBasisVector4 | 0x1cf90 |  |
| TRenderInterface | TKeySequence::GenerateKey | 0x13560 |  |
| TRenderInterface | TRenderInterface::CreateSystemResources | 0xbce0 |  |
| TRenderInterface | TRenderInterface::FindNextResource | 0xc440 |  |

