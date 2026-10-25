#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t src[] = {0x17, 0x39, 0x51, 0x72, 0x94};
    CHECK(hal.nvs.memcpy_to_nvs(33, src, sizeof(src), true) == NVS_TransferResult_OK);
    CHECK(memcmp(memory + 33, src, sizeof(src)) == 0);
    uint16_t crc = calc_checksum(src, sizeof(src));
    CHECK(memory[38] == (uint8_t)crc);
#if NVS_CRC_BYTES > 1
    CHECK(memory[39] == (uint8_t)(crc >> 8));
#endif
    CHECK(memory[32] == 0xA5 && memory[38 + NVS_CRC_BYTES] == 0xA5);
    return 0;
}
