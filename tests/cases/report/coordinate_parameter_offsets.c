#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    coord_system_data_t offset = {.coord = {.x = 1, .y = 2, .z = 3}};
    settings_write_coord_data(CoordinateSystem_G54, &offset);
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[G54:1.000,2.000,3.000]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[G92:0.000,0.000,0.000]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[TLO:0.000,0.000,0.000]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[PRB:0.000,0.000,0.000:0]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
