#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    settings.status_report.probe_coordinates = true;
    char block[] = "G38.2X1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] == 40);
    NEAR(gc_state.position[X_AXIS], sys.position[X_AXIS] / 80.0f);
    CHECK(strcmp(engine_output, "[PRB:0.500,0.000,0.000:1]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
