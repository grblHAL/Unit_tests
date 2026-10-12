#include "support/critical_alarm_host.h"
#include "check.h"

int main(void)
{
    run_critical_alarm_input("G1X10F100\n", 1);
    CHECK(lock_last_status == Status_SystemGClock);
    NEAR(gc_state.position[X_AXIS], 0); CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(strstr(engine_output, "error:9") != NULL);
    return EXIT_SUCCESS;
}
