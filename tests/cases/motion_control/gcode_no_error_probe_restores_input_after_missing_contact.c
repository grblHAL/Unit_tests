#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    explicit_toolsetter_contact = 1600;
    CHECK(explicit_probe_block("G38.3X1F100P1") == Status_OK);
    CHECK(explicit_start_calls == 1 && explicit_start_probe == Probe_Toolsetter);
    CHECK(hal.probe.get_state().probe_id == Probe_Default && explicit_selection_calls == 2);
    CHECK(completed_calls == 1 && !sys.flags.probe_succeeded);
    CHECK(sys.position[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(sys.alarm == Alarm_None);
    CHECK(explicit_probe_block("G0X0") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(sys.position[X_AXIS] == 0 && physical_position[X_AXIS] == 0);
    explicit_toolsetter_contact = 64;
    CHECK(explicit_probe_block("G38.2X1F100P1") == Status_OK);
    CHECK(explicit_start_calls == 2 && explicit_start_probe == Probe_Toolsetter);
    CHECK(explicit_selection_calls == 4 && hal.probe.get_state().probe_id == Probe_Default);
    CHECK(completed_calls == 2 && sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] >= 64 && sys.probe_position[X_AXIS] <= 66);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
