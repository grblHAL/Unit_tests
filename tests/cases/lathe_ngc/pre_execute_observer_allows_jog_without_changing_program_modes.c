#include "support/pre_execute_host.h"
#include "support/jog_motion_host.h"

int main(void)
{
    prepare_jog_motion();
    grbl.on_pre_gcode_execute = observe_pre_execute;
    CHECK(pre_execute_block("G20G91G1F2") == Status_OK);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 50.8f);
    CHECK(plan_get_current_block() == NULL);
    unsigned before = pre_execute_calls;
    char jog[] = "$J=G21G90X1F100";
    CHECK(system_execute_line(jog, hal.stream.write) == Status_OK);
    CHECK(pre_execute_calls == before + 1);
    CHECK(pre_execute_prior_inches && !pre_execute_new_inches);
    NEAR(pre_execute_x, 1);
    NEAR(pre_execute_feed, 100);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 50.8f);
    finish_jog_motion();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 50.8f);
    CHECK(pre_execute_calls == before + 1);
    CHECK(!sys.abort && sys.alarm == Alarm_None && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
