#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    grbl.on_report_options(true);
    CHECK(polar_previous_report_calls == 1);
    CHECK(strstr(engine_output, "KINEMATICS:Polar") == NULL);
    grbl.on_report_options(false);
    CHECK(polar_previous_report_calls == 2);
    CHECK(strstr(engine_output, "[KINEMATICS:Polar v0.03]") != NULL);
    return EXIT_SUCCESS;
}
