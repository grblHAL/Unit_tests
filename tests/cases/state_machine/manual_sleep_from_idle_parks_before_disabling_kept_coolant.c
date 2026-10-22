#include "support/sleep_parking_host.h"
#include "check.h"

int main(void)
{
    prepare_sleep_parking();
    CHECK(state_get() == STATE_IDLE);
    char command[] = "$SLP";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.rt_exec_state & EXEC_SLEEP);
    finish_sleep_parking();
    CHECK(physical_position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
