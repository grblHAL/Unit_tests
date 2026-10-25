#include "support/canned_motion_host.h"

static int32_t maximum_y, minimum_y, quarter_y, three_quarter_y;
static bool quarter_seen, three_quarter_seen;
static void observe_spline(stepper_t *stepper)
{
    pulse_driver(stepper);
    int32_t x = physical_position[X_AXIS], y = physical_position[Y_AXIS];
    if(y > maximum_y) maximum_y = y;
    if(y < minimum_y) minimum_y = y;
    if(!quarter_seen && x >= 1250) { quarter_seen = true; quarter_y = y; }
    if(!three_quarter_seen && x >= 6750) { three_quarter_seen = true; three_quarter_y = y; }
}
int main(void)
{
    prepare_canned_motion();
    hal.stepper.pulse_start = observe_spline;
    execute_canned("G5X100Y0I0J100P0Q-100F100");
    CHECK(quarter_seen && three_quarter_seen);
    /* Bezier t=1/4 and 3/4: (15.625,28.125), (84.375,-28.125) mm. */
    CHECK(abs(quarter_y - 2250) <= 24);
    CHECK(abs(three_quarter_y + 2250) <= 24);
    /* Independent extrema are +/-100/(2*sqrt(3)) mm. */
    CHECK(abs(maximum_y - 2309) <= 24 && abs(minimum_y + 2309) <= 24);
    CHECK(physical_position[X_AXIS] == 8000 && sys.position[X_AXIS] == 8000);
    CHECK(physical_position[Y_AXIS] == 0 && sys.position[Y_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 8000);
    CHECK(axis_pulses[Y_AXIS] == (unsigned)(2 * (maximum_y - minimum_y)));
    CHECK(axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 100);
    NEAR(gc_state.position[Y_AXIS], 0);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
