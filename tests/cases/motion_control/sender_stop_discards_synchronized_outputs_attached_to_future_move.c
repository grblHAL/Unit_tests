#include "support/stop_motion_host.h"
#include "support/io_motion_host.h"
int main(void)
{
    start_stop_motion();
    /* Register virtual expansion outputs through the same public driver API. */
    register_ioports();
    CHECK(io_block("M62P0") == Status_OK);
    CHECK(io_block("M63P1") == Status_OK);
    queue_motion_program("G1X60F100");
    CHECK(output_calls == 0);
    stop_program();
    engine_execute_tasks(STATE_IDLE);
    CHECK(output_calls == 0);
    CHECK(axis_pulses[X_AXIS] < 1600);
    return EXIT_SUCCESS;
}
