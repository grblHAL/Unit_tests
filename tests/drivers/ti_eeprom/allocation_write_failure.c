#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t src[] = {1, 2, 3, 4, 5};
    fail_alloc = true;
    CHECK(hal.nvs.memcpy_to_nvs(33, src, sizeof(src), false) != NVS_TransferResult_OK);
    CHECK(allocations == 1 && writes == 0);
    return 0;
}
