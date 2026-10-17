#include "support/report_host.h"
int main(void)
{
    prepare_report();
    char lathe[] = "2", diameter[] = "G7", inches[] = "1";
    CHECK(settings_store_setting(Setting_Mode, lathe) == Status_OK);
    CHECK(gc_execute_block(diameter) == Status_OK);
    coord_system_data_t fixture = {.coord.values = {12.7f, 25.4f, 38.1f}};
    settings_write_coord_data(CoordinateSystem_G54, &fixture);
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[G54:25.400,25.400,38.100]" ASCII_EOL));
    CHECK(settings_store_setting(Setting_ReportInches, inches) == Status_OK);
    report_init();
    engine_output[0] = 0;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[G54:1.0000,1.0000,1.5000]" ASCII_EOL));
    CHECK(!gc_state.modal.units_imperial && gc_state.modal.diameter_mode);
    coord_system_data_t stored = {0};
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &stored));
    NEAR(stored.coord.x, 12.7f);
    return EXIT_SUCCESS;
}
