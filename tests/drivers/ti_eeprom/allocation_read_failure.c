#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t dst[5] = {9, 9, 9, 9, 9};
    fail_alloc = true;
    CHECK(hal.nvs.memcpy_from_nvs(dst, 33, sizeof(dst), false) != NVS_TransferResult_OK);
    CHECK(allocations == 1 && reads == 0);
    return 0;
}
