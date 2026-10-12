#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.tlo_reference_set.mask = 1u << Z_AXIS;
    sys.tlo_reference[X_AXIS] = 80; sys.tlo_reference[Y_AXIS] = 160; sys.tlo_reference[Z_AXIS] = 240;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[TLR:3.000]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[TLR@:1.000,2.000:2:") != NULL);
    return EXIT_SUCCESS;
}
