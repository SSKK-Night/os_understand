EFI_STATUS status;
status = gBS->ExitBootServices(image_handle, memmap.map_key)
if (EFI_ERROR(status)) {
    Print(L"failed to get memory map: %r\n", status)
    while (1);
}
status = gBS->ExitBootServices(image_handle, memmap.map_key);
if (EFI_ERROR(status)) {
    Print(L"Could not exit boot service: %r\n", status);
    while (1);
}

UINT64 entry_addr = *(UINT64*)(kernel_base_addr + 24);

typedef void EntryPointType(void);
EntryPointType* entry_point = (EntryPointType*)entry_addr;
entry_point();