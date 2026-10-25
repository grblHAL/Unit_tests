#include "support/probe_motion_host.h"

int main(void)
{
    prepare_probe_motion();
    contact_steps = 120;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    char unsupported[] = "G38.6X2F100";
    CHECK(gc_execute_block(unsupported) == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    CHECK(completed_calls == 0 && !hal.probe.get_state().is_probing);
    CHECK(sys.probing_state == Probing_Off && !sys.flags.probe_succeeded);
    CHECK(axis_pulses[X_AXIS] == 0 && physical_position[X_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.feed_rate, 100);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    char retry[] = "G38.2X2F100";
    CHECK(gc_execute_block(retry) == Status_OK);
    CHECK(sys.flags.probe_succeeded && sys.probe_position[X_AXIS] == 120);
    CHECK(completed_calls == 1 && sys.probing_state == Probing_Off);
    CHECK(!hal.probe.get_state().is_probing && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] >= 120 && physical_position[X_AXIS] < 160);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(axis_pulses[X_AXIS] == (unsigned)physical_position[X_AXIS]);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], (float)sys.position[X_AXIS] / settings.axis[X_AXIS].steps_per_mm);
    CHECK(state_get() == STATE_IDLE && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
