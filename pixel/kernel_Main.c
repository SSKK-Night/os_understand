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

void CalcLoadAddressRange(Elf64_Ehdr* ehdr, UINT64* first, UINT64* last) {
    Elf64_Phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->e_phoff);
    *first = MAX_UINT64;
    *last = 0;
    for (Elf64_Half i = 0; i < ehdr->e_phnum; ++i) {
        if (phdr[i].p_type != PT_LOAD) continue;
        *first = MIN(*first, phdr[i].p_vaddr);
        *last = MAX(*last, phdr[i].p_vaddr + phdr[i].p_memsz);
    }
}

CopyLoadSegments(kernel_ehdr);
Print(L"kernel: 0x%0lx - 0x%0lx\n", kernel_first_addr, kernel_last_addr);

status = gBS->FreePool(kernel_buffer);
if (EFI_ERROR(status)) {
    Print(L"failed to free pool: %r\n", status);
    Halt();
}

void CopyLoadSegments(Elf64_Ehdr* ehdr) {
    Elf64_Phdr* phdr = (Elf64_Phdr*)((UINT64)ehdr + ehdr->ehoff);
    for (Elf64_Half i = 0, i < ehdr->e_phnum; ++i) {
        if (phdr[i].p_type != PT_LOAD) continue;

        UINT64 segm_in_file = (UINT64)ehdr + phdr[i].p_offset;
        CopyMem((VOID*)phdr[i].p_vaddr, (VOID*)segm_in_file, phdr[i].p_filesz);

        UINT remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz;
        SetMem((VOID*)(phdr[i].p_vaddr + phdr[i].p_filesz), remain_bytes, 0);
    }
}