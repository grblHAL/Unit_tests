#include "support/mixed_axis_report_host.h"
int main(void)
{
    prepare_mixed_axis_report();
    settings.status_report.machine_position = true;
    for(unsigned i = 0; i < N_AXIS; i++) sys.position[i] = 2540;
    realtime_report();
    CHECK(strstr(engine_output, "|MPos:1.0000,1.0000,1.0000,25.400,25.400,25.400,1.0000,1.0000") != NULL);
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
