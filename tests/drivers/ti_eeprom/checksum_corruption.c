#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t src[] = {1, 2, 3, 4, 5}, dst[5] = {0};
    ti_seed(33, src, sizeof(src));
    CHECK(hal.nvs.memcpy_from_nvs(dst, 33, sizeof(dst), true) == NVS_TransferResult_OK);
    memory[38] ^= 1;
    CHECK(hal.nvs.memcpy_from_nvs(dst, 33, sizeof(dst), true) != NVS_TransferResult_OK);
    CHECK(hal.nvs.memcpy_from_nvs(dst, 33, sizeof(dst), false) == NVS_TransferResult_OK);
    CHECK(memcmp(src, dst, sizeof(src)) == 0);
    return 0;
}
