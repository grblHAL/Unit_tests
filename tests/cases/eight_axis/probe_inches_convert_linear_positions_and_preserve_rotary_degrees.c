#include "support/mixed_axis_report_host.h"
int main(void)
{
    prepare_mixed_axis_report();
    for(unsigned i = 0; i < N_AXIS; i++) sys.probe_position[i] = -2540;
    sys.flags.probe_succeeded = true;
    report_probe_parameters();
    CHECK(strcmp(engine_output, "[PRB:-1.0000,-1.0000,-1.0000,-25.400,-25.400,-25.400,-1.0000,-1.0000:1]" ASCII_EOL) == 0);
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
