#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("$C\nG1X1F100\n", 2);
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(strstr(engine_output, "ok" ASCII_EOL "ok" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
