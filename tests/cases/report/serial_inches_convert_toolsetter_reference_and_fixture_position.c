#include "support/report_host.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    report_init();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    sys.tlo_reference[X_AXIS] = 4064;
    sys.tlo_reference[Y_AXIS] = 6096;
    sys.tlo_reference[Z_AXIS] = 2032;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[TLR:1.0000]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[TLR@:2.0000,3.0000:2:") != NULL);
    CHECK(sys.tlo_reference[Z_AXIS] == 2032);
    return EXIT_SUCCESS;
}
