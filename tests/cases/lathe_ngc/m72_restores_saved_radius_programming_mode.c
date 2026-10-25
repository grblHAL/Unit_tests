#include "support/css_host.h"
#include "support/named_parameter_host.h"
#include "report.h"
int main(void)
{
    prepare_css_parser(true);
    report_init_fns(); report_init();
    CHECK(css_block("G8") == Status_OK);
    CHECK(css_block("M70") == Status_OK);
    CHECK(css_block("G7") == Status_OK);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G7 ") != NULL);
    CHECK(strstr(engine_output, " G8 ") == NULL);
    CHECK(css_block("M72") == Status_OK);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G8 ") != NULL);
    CHECK(strstr(engine_output, " G7 ") == NULL);
    NEAR(read_named_parameter("_lathe_diameter_mode"), 0);
    NEAR(read_named_parameter("_lathe_radius_mode"), 1);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
