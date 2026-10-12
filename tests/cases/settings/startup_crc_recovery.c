#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    stored_line_t source = "G21G90", result = {0};
    settings_write_startup_line(0, source);
    hal.nvs.put_byte(NVS_ADDR_STARTUP_BLOCK, hal.nvs.get_byte(NVS_ADDR_STARTUP_BLOCK) ^ 1);
    CHECK(!settings_read_startup_line(0, result));
    CHECK(result[0] == '\0');
    CHECK(settings_read_startup_line(0, result));
    CHECK(result[0] == '\0');
    return EXIT_SUCCESS;
}
