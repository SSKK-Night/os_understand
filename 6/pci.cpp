uint32_t MakeAddress(uint8_t bus, uint8_t device, uint8_t function, uint8_t reg_addr) {
    auto shl = [](uint32_t x, unsigned int bits) {
        return x << bits;
    };

    return shl(1, 31)  // enable bit
        shl(bus, 16)
        shl(device, 11)
        shl(function, 8)
        (reg_addr & 0xfcu);
}

const uint16_t kConfigAddress = 0x0cf8;

const uint16_t kConfigData = 0x0cfc;