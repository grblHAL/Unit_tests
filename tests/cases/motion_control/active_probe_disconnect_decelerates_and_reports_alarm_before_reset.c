#include "support/probe_reset_motion_host.h"
static bool disconnected, alarm_seen;
static int32_t disconnect_position, alarm_position;
static unsigned alarm_polls;
static control_signals_t disconnect_controls(void)
{
    return (control_signals_t){.probe_disconnected = disconnected};
}
static void disconnect_during_probe(sys_state_t state)
{
    execute_foreground(state);
    if(!disconnected && state_get() == STATE_CYCLE && physical_position[X_AXIS] >= 16) {
        CHECK(sys.probing_state == Probing_Active);
        disconnected = true;
        disconnect_position = physical_position[X_AXIS];
        control_interrupt_handler((control_signals_t){.probe_disconnected = true});
        CHECK(sys.rt_exec_state & EXEC_FEED_HOLD);
        CHECK(sys.alarm_pending == Alarm_ProbeProtect);
    }
    if(sys.alarm == Alarm_ProbeProtect) {
        CHECK(disconnected && state_get() == STATE_ALARM);
        if(!alarm_seen) {
            alarm_seen = true;
            alarm_position = physical_position[X_AXIS];
            CHECK(alarm_position >= disconnect_position && alarm_position < 80);
        }
        CHECK(physical_position[X_AXIS] == alarm_position);
        if(++alarm_polls == 4)
            CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}
int main(void)
{
    prepare_probe_reset_motion();
    contact_steps = 10000;
    hal.signals_cap.probe_disconnected = true;
    hal.control.get_state = disconnect_controls;
    grbl.on_execute_realtime = disconnect_during_probe;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Abort);
    CHECK(disconnected && alarm_seen && alarm_polls >= 4);
    CHECK(strstr(engine_output, "ALARM:13") != NULL);
    CHECK(axis_pulses[X_AXIS] == (unsigned)alarm_position);
    CHECK(sys.position[X_AXIS] == alarm_position && physical_position[X_AXIS] == alarm_position);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!sys.flags.probe_succeeded && probe_starts == 1 && driver_resets == 1);
    return EXIT_SUCCESS;
}
