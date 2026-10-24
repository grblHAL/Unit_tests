#include "ti_host.h"
int main(void)
{
    ti_prepare();
    for (unsigned offset = 0; offset < 4; offset++)
        for (unsigned length = 1; length <= 9; length++)
        {
            memset(memory, 0xA5, sizeof(memory));
            uint8_t src[9], dst[9] = {0};
            for (unsigned i = 0; i < length; i++)
                src[i] = (uint8_t)(i + length);
            CHECK(hal.nvs.memcpy_to_nvs(32 + offset, src, length, false) == NVS_TransferResult_OK);
            CHECK(hal.nvs.memcpy_from_nvs(dst, 32 + offset, length, false) ==
                  NVS_TransferResult_OK);
            CHECK(memcmp(src, dst, length) == 0);
            for (unsigned i = 0; i < sizeof(memory); i++)
                CHECK(
                    memory[i] ==
                    ((i >= 32 + offset && i < 32 + offset + length) ? src[i - 32 - offset] : 0xA5));
        }
    return 0;
}
