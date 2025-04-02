struct FrameBufferConfig config = {
    (UINT8*)gop->Mode->FrameBufferBase,
    gop->Mode->Info->PixelsPerScanLine,
    gop->Mode->Info->HorizontalResolution,
    gop->Mode->Info->VerticalResolution,
    0
};

switch (gop->Mode->Info->PixelFromat) {
    case PixelRedGreenBlueReserved8BitPerColor:
        config.pixel_format = kPixelRGBResv8BitPerColor;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        config.pixel_format = kPixelBGRResv8BitPerColor;
        break;
    default:
        Print(L"Unimplemented pixel format: %d\n", gop->Mode->Info->PixelFormat);
        Halt();
}

typedef void EntryPointType(const struct FrameBufferConfig*);
EntryPointType* entry_point = (EntryPointType*)entry_addr;
entry_point(&config);