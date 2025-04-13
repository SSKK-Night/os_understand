EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
UINTN kernel_file_size = file_info->FileSize;

VOID* kernel_buffer;
status = gBS->AllocatePool(EfiLoaderData, kernel_file_size, &kernel_buffer);
if (EFI_ERROR(status)) {
    Print(L"failed to allocate pool: %r\n", status);
    Halt();
}
status = kernel_file->Read(kernel_file, &kernel_file_size, kernel_buffer);
if (EFI_ERROR(status)) {
    Print(L"error: %r", status);
    Halt();
}

Elf64_Ehdr* kernel_ehdr = (Elf64_Ehdr*)kernel_buffer;
UINT64 kernel_first_addr, kernel_last_addr;
CalcLoadAddressRange(kernel_ehdr, &kernel_first_addr, &kernel_last_addr);

UINT num_pages = (kernel_last_addr - kernel_first_addr + 0xfff) / 0x1000;
status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, num_pages, &kernel_first_addr);

if (EFI_ERROR(status)) {
    Print(L"failed to allocate pages: %r\n", status);
    Halt();
}