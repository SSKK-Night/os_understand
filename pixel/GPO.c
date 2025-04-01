EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
OpenGOP(image_handle, &gop);
Print(L"Resolution: %ux%u, Pixel Format: %s, %u pixels/line\n",
    gop->Mode->Info->HorizontalResolution,
    gop->Mode->Info->VerticalResolution,
    GetPixelFormatUnicode(gop->Mode->Info->PixelFormat),
    gop->Mode->Info->PixelsPerScanLine)
Print(L "Frame Buffer: 0x%0lx - 0x%0lx, Size: %lu bytes\n"
    gop->Mode->FrameBufferBase,
    gop->Mode->FrameBufferBase + gop->Mode->FrameBufferSize,
    gop->Mode->FrameBufferSize);

UINT8* frame_buffer = (UINT8*)gop->Mode->FrameBufferBase;
for (UINT i = 0; i < gop->Mode->FrameBufferSize; ++i) {
    frame_buffer[i] = 255;
}