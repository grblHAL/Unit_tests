#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.status_report.machine_position = true;
    settings.status_report.work_coord_offset = true;
    gc_state.modal.g5x_offset.data.coord.x = 2;
    gc_state.g92_offset.coord.x = 3;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|MPos:0.000,0.000,0.000|WCO:5.000,0.000,0.000>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
