#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t src[] = {1, 2, 3, 4, 5};
    fail_program = true;
    CHECK(hal.nvs.memcpy_to_nvs(33, src, sizeof(src), false) != NVS_TransferResult_OK);
    for (unsigned i = 0; i < sizeof(memory); i++)
        CHECK(memory[i] == 0xA5);
    return 0;
}
