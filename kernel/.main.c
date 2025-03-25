EFI_FILE_PROTOCOL* kernel_file;
root_dir->(
    root_dir, &kernel_file. L"\\kernel.elf",
    EFI_FILE_MODE_READ, 0
);

UINT file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12
UINT file_info_buffer[file_info_size];
kernel_file->GetInfo(
    kernel_file, &gEfiFileInfoGuide,
    &file_info_size, file_info_buffer
);

EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
UINT kernel_file_size = file_info->FileSize;

EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
gBS->AllocatePages(
    AllocateAddress, EfiLoaderData,
    (kernel_file_size + 0xfff) / 0x1000, &kernel_base_addr
);
kernel_file->Read(kernel_file, &kernel_file_size, (VOID*)kernel_base_addr);
Print(L"Kernel: 0x%0lx (%lu bytes)\n", kernel_base_addr, kernel_file_size);