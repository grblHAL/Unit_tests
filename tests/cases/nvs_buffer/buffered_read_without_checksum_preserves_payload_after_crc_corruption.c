#include "support/nvs_retry_host.h"

int main(void)
{
    nvs_address_t address = prepare_retry_nvs(true);
    uint8_t payload[] = {11,22,33}, result[3];
    CHECK(hal.nvs.memcpy_to_nvs(address, payload, sizeof(payload), true));
    hal.nvs.put_byte(address + sizeof(payload), hal.nvs.get_byte(address + sizeof(payload)) ^ 1);
    CHECK(!hal.nvs.memcpy_from_nvs(result, address, sizeof(result), true));
    CHECK(hal.nvs.memcpy_from_nvs(result, address, sizeof(result), false));
    CHECK(memcmp(result, payload, sizeof(result)) == 0); nvs_buffer_free();
    return EXIT_SUCCESS;
}
