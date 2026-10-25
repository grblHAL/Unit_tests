#include "support/spindle_broadcast_host.h"
static unsigned notifications[3];
static spindle_state_t notified_states[3];
static void observe_programmed(spindle_ptrs_t *spindle, spindle_state_t state,
                               float rpm, spindle_rpm_mode_t mode)
{
    CHECK(spindle->id == 0 || spindle->id == 1);
    CHECK(spindle == spindle_get(spindle->id));
    CHECK(mode == SpindleSpeedMode_RPM);
    NEAR(rpm, spindle->id == 0 ? 3000 : 7000);
    notifications[spindle->id]++;
    notified_states[spindle->id] = state;
}
int main(void)
{
    start_clockwise_broadcast_fixture();
    grbl.on_spindle_programmed = observe_programmed;
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(notifications[0] == 1 && notifications[1] == 1);
    CHECK(!notified_states[0].on && !notified_states[1].on);
    unsigned stopped0 = spindle_output_calls[0], stopped1 = spindle_output_calls[1];
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(notifications[0] == 2 && notifications[1] == 2);
    CHECK(spindle_output_calls[0] == stopped0 && spindle_output_calls[1] == stopped1);
    CHECK(spindle_program_block("M3$0") == Status_OK);
    CHECK(notifications[0] == 3 && notifications[1] == 2);
    CHECK(spindle_program_block("M3$-1") == Status_OK);
    CHECK(notifications[0] == 4 && notifications[1] == 3);
    check_broadcast_outputs(false);
    CHECK(spindle_program_block("M4$-1") == Status_OK);
    CHECK(notifications[0] == 5 && notifications[1] == 4);
    CHECK(notified_states[0].on && notified_states[0].ccw);
    CHECK(notified_states[1].on && notified_states[1].ccw);
    check_broadcast_outputs(true);
    CHECK(notifications[2] == 0);
    return EXIT_SUCCESS;
}
