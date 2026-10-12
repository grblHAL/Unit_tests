#include "support/canned_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_spindle();
    CHECK(canned_block("M4S1000") == Status_OK);
    canned_spindle_events = 0;
    execute_canned("G84Z-1R0P0F100");
    CHECK(axis_pulses[Z_AXIS] == 160);
    CHECK(physical_position[Z_AXIS] == 0);
    CHECK(canned_spindle_events == 3);
    CHECK(!canned_spindle_log[0].state.on);
    CHECK(canned_spindle_log[0].z == -80);
    CHECK(canned_spindle_log[1].state.on);
    CHECK(canned_spindle_log[1].state.ccw == false);
    CHECK(canned_spindle_log[1].z == -80);
    CHECK(canned_spindle_log[2].state.on);
    CHECK(canned_spindle_log[2].state.ccw == true);
    CHECK(canned_spindle_log[2].z == 0);
    NEAR(canned_spindle_log[2].rpm, 1000);
    CHECK(!sys.override.control.feed_hold_disable);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!spindle_get(0)->param->option.override_disable);
    return EXIT_SUCCESS;
}
