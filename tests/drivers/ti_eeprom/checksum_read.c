#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t src[] = {0x17, 0x39, 0x51, 0x72, 0x94}, dst[5] = {0};
    ti_seed(33, src, sizeof(src));
    CHECK(hal.nvs.memcpy_from_nvs(dst, 33, sizeof(dst), true) == NVS_TransferResult_OK);
    CHECK(memcmp(src, dst, sizeof(src)) == 0);
    return 0;
}
