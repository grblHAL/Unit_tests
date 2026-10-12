#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    nvs_address_t first = nvs_alloc(5), second = nvs_alloc(7);
    CHECK(first >= GRBL_NVS_SIZE);
    CHECK(first % 4 == 0 && second % 4 == 0);
    CHECK(second >= first + 5 + NVS_CRC_BYTES);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
