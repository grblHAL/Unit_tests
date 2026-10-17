#include "support/mixed_axis_report_host.h"
int main(void)
{
    prepare_mixed_axis_report();
    for(unsigned i = 0; i < N_AXIS; i++) sys.home_position[i] = 25.4f;
    sys.homed.mask = (1u << 0) | (1u << 3) | (1u << 7);
    settings.homing.flags.enabled = true;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[HOME:1.0000,1.0000,1.0000,25.400,25.400,25.400,1.0000,1.0000:137]" ASCII_EOL) != NULL);
    CHECK(sys.homed.mask == 137);
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
