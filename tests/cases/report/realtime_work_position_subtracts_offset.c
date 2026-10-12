#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.position[X_AXIS] = 800;
    gc_state.modal.g5x_offset.data.coord.x = 2;
    gc_state.g92_offset.coord.x = 3;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|WPos:5.000,0.000,0.000>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
