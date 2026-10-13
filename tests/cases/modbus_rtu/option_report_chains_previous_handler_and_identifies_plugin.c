#include "support/rtu_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    grbl.on_report_options(true);
    CHECK(option_report_calls == 1 && option_report_new);
    CHECK(strstr(engine_output, "MODBUS") == NULL);
    grbl.on_report_options(false);
    CHECK(option_report_calls == 2 && !option_report_new);
    CHECK(strstr(engine_output, "MODBUS") != NULL);
    CHECK(strstr(engine_output, "[PLUGIN:MODBUS v") != NULL);
    return EXIT_SUCCESS;
}
