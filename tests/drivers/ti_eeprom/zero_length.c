#include "ti_host.h"
int main(void)
{
    ti_prepare();
    uint8_t value = 7;
    CHECK(hal.nvs.memcpy_to_nvs(32, &value, 0, false) == NVS_TransferResult_OK);
    CHECK(hal.nvs.memcpy_from_nvs(&value, 32, 0, false) == NVS_TransferResult_OK);
    CHECK(value == 7);
    for (unsigned i = 0; i < sizeof(memory); i++)
        CHECK(memory[i] == 0xA5);
    return 0;
}
