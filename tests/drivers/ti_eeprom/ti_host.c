#include "ti_host.h"
grbl_hal_t hal;
uint8_t memory[1024];
unsigned reads, writes, allocations;
bool fail_alloc, fail_program;
void *ti_malloc(size_t size)
{
    CHECK(size <= sizeof(memory));
    allocations++;
    return fail_alloc ? NULL : malloc(size);
}
void EEPROMRead(uint32_t *data, uint32_t address, uint32_t size)
{
    CHECK(address % 4 == 0 && size % 4 == 0 && address + size <= sizeof(memory));
    reads++;
    memcpy(data, memory + address, size);
}
uint32_t EEPROMProgram(uint32_t *data, uint32_t address, uint32_t size)
{
    CHECK(address % 4 == 0 && size % 4 == 0 && address + size <= sizeof(memory));
    writes++;
    if (fail_program)
        return EEPROM_RC_NOPERM;
    memcpy(memory + address, data, size);
    return 0;
}
void ti_prepare(void)
{
    memset(memory, 0xA5, sizeof(memory));
    eeprom_init();
    CHECK(hal.nvs.type == NVS_EEPROM);
}
void ti_seed(uint32_t address, const uint8_t *data, size_t size)
{
    CHECK(address + size + NVS_CRC_BYTES <= sizeof(memory));
    memcpy(memory + address, data, size);
    uint16_t crc = calc_checksum(data, size);
    memory[address + size] = crc & 0xFF;
#if NVS_CRC_BYTES > 1
    memory[address + size + 1] = crc >> 8;
#endif
}
