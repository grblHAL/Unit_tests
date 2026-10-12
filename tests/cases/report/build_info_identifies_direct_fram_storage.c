#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    nvs_buffer_get_physical()->type = NVS_FRAM;
    hal.nvs.type = NVS_FRAM;
    hal.nvs.size_max = 8192;
    build_report(true);
    CHECK(strstr(engine_output, "[NVS STORAGE:FRAM 8K]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
