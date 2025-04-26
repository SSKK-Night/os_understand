const uint8_t kFontA[16] = {
    0b00000000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00100100,
    0b00100100,
    0b00100100,
    0b00100100,
    0b01111110,
    0b01000010,
    0b01000010,
    0b01000010,
    0b11100111,
    0b00000000,
    0b00000000,
}

void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color) {
    if (c != 'A') {
        return;
    }
    for (int dy = 0; dy < 16; ++dy) {
        for (int dx = 0; dx < 8; ++dx) {
            if ((kFontA[dy] << dx) & 0x80u) {
                writer.Write(x + dx, y + dy, color);
            }
        }
    }
}

WriteAscii(*pixel_writer, 50, 50, 'A', {0, 0, 0});
WriteAscii(*pixel_writer, 58, 50, 'A', {0, 0, 0});

int i = 0;
for (char c = '!'; c <= '~'; ++c, ++i) {
    WriteAscii(*pixel_writer, 8 * i, 50, c, {0, 0, 0});
}
WriteString(*pixel_writer, 0, 66, "Hello, world!", {0, 0, 255});

char buf[128];
sprintf(buf, "1 + 2 = %d", 1 + 2);
WriteString(*pixel_writer, 0, 82, buf, {0, 0, 0});


int printk(const char* format, ...) {
    va_list ap;
    int result;
    char s[1024];

    va_start(ap, format);
    result = vsprintf(s, format, ap);
    va_end(ap);

    cosole->PutString(s);
    return result;
}

for (int i = 0; i < 27; ++i) {
    printk("printk: %d\n", i);
}