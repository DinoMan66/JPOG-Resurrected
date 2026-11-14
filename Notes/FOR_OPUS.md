# For Opus - functions handed off by Sonnet sessions

Sonnet sessions write the functions that are too hard for a quick attempt here instead of spending their budget on
them (CLAUDE.md "Hand-off to Opus"). Opus sessions work this list top to bottom with the same rules and budgets,
and tick entries off. One line per function:

`- [ ] Class::method | address | Src file | why handed off | what is known / tried | best lead`

Tick with `- [x] ... -> MATCH (round N)` or `- [x] ... -> parked in OPEN_WALLS.md (why)`; keep ticked lines for a
week, then delete them.

## Open
- [ ] TInputDXInterface::EnumerateDeviceCallback | TInputDXInterface 0x3890 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TInputDevice::ProcessRepeats | TInputInterface 0x1560 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TMemory::dtor | TKernelInterface 0x1ec30 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TCameraViewportHandler::GetRenderer | TRenderInterface 0xeb30 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TRenderInterface::DestroyResourceTypeRecurse | TRenderInterface 0xc1f0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSkeleton::GetBone | TRenderInterface 0x80f0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSkinMesh::dtor | TRenderInterface 0x180d0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TTransformObject::GetLocalMatrix | TRenderInterface 0x11db0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TGUIStyle::InitialiseStatic | TGuiInterface 0x15da0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TGUIWidget::InitialiseStatic | TGuiInterface 0x1b510 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TGUIWindow::InitialiseStatic | TGuiInterface 0x21660 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSumOfMinterms::ctor | TKernelInterface 0x1f160 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TAnimation::GetSequencePtr | TRenderInterface 0x8740 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TKeyframeLibraryInstance::dtor | TRenderInterface 0x68f0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TKeyframeLibraryManager::DebugDump | TRenderInterface 0x58e0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TResource::IsValid | TRenderInterface 0x12f20 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSkeleton::GetSequence | TRenderInterface 0x80b0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSumOfMinterms::ctor | TKernelInterface 0x1f1f0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSumOfMinterms::ctor | TKernelInterface 0x1f260 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TLightingNode::Render | TRenderInterface 0x103d0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TTerrainObject::Render | TRenderInterface 0x116a0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TGUILayoutManager::DeinitialiseStatic | TGuiInterface 0x12580 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TInputDXDeviceKeyboard::EnumObjectCallback | TInputDXInterface 0x2a60 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TThreadManager::FindThread | TKernelInterface 0x7e50 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TModel::CreateInstance | TRenderInterface 0x9670 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] TSun::ComputeAttenuation | TRenderInterface 0x18da0 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order
- [ ] PProperties::PutPropertyUnique | PPropertyParser 0x1390 | | 'inl' group: original calls a helper our build inlines | inl | test the inline-budget lead (FROM_ZOO.md 1) and definition order

Seeded 2026-11-13 with NOT_MATCHING.md's 'inl' group (FROM_ZOO.md lead 1). The rest of NOT_MATCHING.md
(regalloc, shrink-wrap, branch, ...) is the wider backlog once this list is done.
- [ ] TGUIInterface::FindWidgetClass/FindLayoutClass/FindComponentClass | TGuiInterface | | shrink-wrap: original loads the name once before the loop, no register pushes | shrink-wrap | 1/2 attempts used; try a different loop shape
- [ ] TGUIInterface::FindFont | TGuiInterface | | shrink-wrap, filed compiler-limited 2/2 | shrink-wrap | one re-check only
- [ ] TGUIInterface::DeleteAllSkus | TGuiInterface | | regalloc (original uses ecx), 1/2 | regalloc | m_oSkus.Clear()
- [ ] TGUIScreen DoButtonPress/DoPointerMove family | TGuiInterface 0x15200 | | operate on the TGUIInputManager subobject at +0x8c, needs TGUIInputManager slot 5 | class | declare input-manager slots first
- [ ] TGUIWidgetAction new/delete/GetFreeList | TGuiInterface | | freelist family, needs the forbidden stamping macro | wall | ask the user
- [ ] TGUIFunction copy ctor (+ Sawtooth/Sine/Constant ctors) | TGuiInterface 0x72d0 | | original copies +8,+4,+0x10,+0xC; reordering the mem-initialisers changed nothing | regalloc | 1/2 used; look for a different copy shape
- [ ] PGUIRowData/PGUIItemData Clone + copy ctors | PGUICore 0x6060/0x60a0/0x6170/0x61b0 | | classes are abstract in our headers (TObject pure virtuals GetClass etc. not declared); original copy ctors copy only +0x14/+0x18 (RowData) and +0x10/+0x14 (ItemData) | class | declare the TObject slots, then Clone = new(tmalloc(size,0,-1)) X(*this)
- [ ] TIndexBlockResource IsLocked/Invalidate/Unlock | TRenderD3DInterface 0xbc00/0xbc90/0xba20 | | same source shape as the matching TVertexBlockResource versions but regalloc differs (orig mov eax,[ecx+0x44]; test; ours edx/xor) | regalloc | 1/2 used
- [ ] TVertexBlockResource ctor + HALBuffer sub-struct layout | TRenderD3DInterface | | member +0x54..0x74 layout unconfirmed | class | check ctor against dtor/CreateHAL
- [ ] TRenderCaptureD3D ctor | TRenderD3DInterface | | original inlines the base ctor, ours calls the import | shrink-wrap | 1/2 used
- [ ] TModelD3D | TRenderD3DInterface | | TModel.h slot names disagree with the real slots (Create/Delete/Load/Unload/LoadTMDHAL) | class | rename slots from TRenderInterface sources first
- [ ] Vertex/Index pool + factory resources, TD3DAdapter covariance for GetCurrentDevice, TTEXTURERESOURCEFORMAT enum values 1/2, imported Clamp 0x1003f16c, TRenderCaptureD3D::Request (832 B), TD3DAssert definition, ms_oFreelist ctor args | TRenderD3DInterface | | structural | class | one line per class when picked up
- [ ] TRenderD3DInterface::IsTextureFormatSupported(TTEXTURERESOURCEFORMAT) | 0x8560 | TRenderD3DInterface\TRenderD3DInterface.cpp | 2/2 used, branch | original puts the format 1 block (mov eax,0x15) at the end and the je for 1 jumps there; both if-chain and local-variable forms give an earlier target | branch | try a switch; also overload IsTextureFormatSupported(_D3DFORMAT) 0x85b0 needs the Device/adapter helper chain (0x79b0, 0x7740) named first
- [ ] TRenderD3DInterface::Supports32BitTextures | 0x8630 | TRenderD3DInterface\TRenderD3DInterface.cpp | filed 2/2, orig keeps esi, ours ebp; ours also merges the two return-false paths | regalloc | depends on IsTextureFormatSupported shape
- [ ] TMSWindow::Destroy | 0x5990 | TRenderD3DInterface\TMSWindow.cpp | 1/2 used: original CALLS GetHWND/Disable (ours inlines them), same in the ctor 0x5810 (calls Destroy) | inline | ctor/Create/Destroy probably sit in another TU than the accessors (TRenderD3DInterface.cpp?); test moving them
- [ ] TVertexBlockResource::DestroyHAL | 0xa8f0 | TRenderD3DInterface\TD3DVertexBlockResource.cpp | 2/2 used, SAFE_RELEASE macro now in d3d8min.h (index DestroyHAL and DestroyDisplay match with it), vertex frame is 4 bytes bigger (esp+0xac vs 0xa8) | stack | original has one more local, probably the factory/vertex format pointer
- [ ] TRenderD3DInterface::DestroyAdapterDatabase | 0x9ad0 | TRenderD3DInterface\TRenderD3DInterface.cpp | 1/2 used, shrink-wrap (orig push ebx/call import first, ours sub esp,0xc); node pointer = object + 4 (TRenderAdapter has a vtable before its TNode) | shrink-wrap | TNodeList T* vs node pointer conversion
- [ ] TOrderTable::DeregisterMaterial/Render | 0x5ef0/0x5ff0 | TRenderD3DInterface\TOrderTable.cpp | not tried: DeregisterMaterial is the InsertTail family wall; Render needs the TRenderInterface C export _TRenderInterface_GetFlushShaderSorted@0 (undeclared) | class | declare the export first
- [ ] TRenderD3DInterface BeginScene/EndScene/Update/Create/Destroy/LoadShaders/ResetDevice/LostDevice, GetMaxTextureWidth/Height (Device caps helper 0x7740), ConnectDefaultViewportHandlers (listener class 0x47a0), IsCapableColourCorrection (D3DCAPS8 struct), TransformGamma (x87 + TMath::Pow), D3DGetErrorString/DescriptionString (internal helpers 0x3386b/0x38b87), TD3DAssert | TRenderD3DInterface | | need device/emitter/TWString/TCString structure | class | one class header (emitters + TWString) unlocks most of them
- [ ] TIndexBlockResource implicit copy ctor | 0xbd90 | TRenderD3DInterface\TD3DIndexBlockResource.cpp | 2/2 used: original copies +0x4c as a dword while the default ctor zeroes a word there | source | the member at +0x4C is probably a small struct or a pair that ICC copies as one dword; ours (two ushorts) copies the word only
