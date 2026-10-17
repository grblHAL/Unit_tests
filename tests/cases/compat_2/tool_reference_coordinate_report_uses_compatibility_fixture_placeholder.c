#include "support/report_host.h"
int main(void)
{
    prepare_report();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    sys.tlo_reference[X_AXIS] = 80;
    sys.tlo_reference[Y_AXIS] = 160;
    sys.tlo_reference[Z_AXIS] = 800;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[TLR:10.000]" ASCII_EOL));
    CHECK(strstr(engine_output, "[TLR@:1.000,2.000:2:0]" ASCII_EOL));
    CHECK(sys.tlo_reference_set.mask == Z_AXIS_BIT);
    CHECK(sys.tlo_reference[Z_AXIS] == 800);
    return EXIT_SUCCESS;
}
