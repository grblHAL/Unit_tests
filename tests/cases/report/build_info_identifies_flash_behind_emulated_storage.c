#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    nvs_buffer_get_physical()->type = NVS_Flash;
    hal.nvs.type = NVS_Emulated;
    hal.nvs.size_max = 16384;
    build_report(true);
    CHECK(strstr(engine_output, "[NVS STORAGE:*FLASH 16K]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
