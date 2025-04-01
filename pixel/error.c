EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
status = gBS->AllocatePages(
    AllocateAddress, EfiLoaderData,
    (kernel_file_size + 0xfff) / 0x1000, &kernel_base_addr);
if (EFI_ERROR(status)) {
    Print(L"failed to allocate pages: %r", status);
    Halt();
}