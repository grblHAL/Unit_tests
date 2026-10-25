#include "support/probe_motion_host.h"

int main(void)
{
    prepare_probe_motion();
    grbl.on_probe_completed = NULL;
    contact_steps = 0;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_FailInit);
    CHECK(sys.alarm == Alarm_ProbeFailInitial && !sys.flags.probe_succeeded);
    CHECK(sys.probing_state == Probing_Off && !hal.probe.get_state().is_probing);
    CHECK(completed_calls == 0 && plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    contact_steps = 40;
    char unlock[] = "$X";
    CHECK(system_execute_line(unlock, hal.stream.write) == Status_OK);
    CHECK(sys.alarm == Alarm_None && state_get() == STATE_IDLE);
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Found);
    CHECK(sys.flags.probe_succeeded && sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 0 && sys.alarm == Alarm_None);
    CHECK(sys.probing_state == Probing_Off && !hal.probe.get_state().is_probing);
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] >= 40 && sys.position[X_AXIS] < 80);
    return EXIT_SUCCESS;
}
