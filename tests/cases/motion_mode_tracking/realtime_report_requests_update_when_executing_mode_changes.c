#include "support/motion_mode_host.h"
static unsigned status_mode_changes, last_observed_change;
static void status_changed(void) { status_mode_changes++; }
static void poll_status(void)
{
    status_report_tracking_t tracking = {0};
    engine_output[0] = 0; report_realtime_status(hal.stream.write, &tracking);
    engine_output[0] = 0;
}
static void status_tracking_pulse(stepper_t *stepper)
{
    tracked_mode_pulse(stepper);
    if(stepper->step_out.mask && mode_changes != last_observed_change) {
        last_observed_change = mode_changes;
        system_clear_exec_state_flag(EXEC_GCODE_REPORT);
        poll_status();
        CHECK(sys.rt_exec_state & EXEC_GCODE_REPORT);
        CHECK(status_mode_changes == mode_changes);
        system_clear_exec_state_flag(EXEC_GCODE_REPORT);
        poll_status();
        CHECK(!(sys.rt_exec_state & EXEC_GCODE_REPORT));
        CHECK(status_mode_changes == mode_changes);
    }
}
int main(void)
{
    prepare_motion_modes(); settings.status_report.parser_state = true;
    queue_motion_program("G0X1"); queue_motion_program("G1X2F100");
    /* Settle the report's cached parser fields before testing execution changes. */
    poll_status(); poll_status(); poll_status();
    grbl.on_gcode_mode_changed = status_changed;
    hal.stepper.pulse_start = status_tracking_pulse;
    execute_motion_program();
    CHECK(status_mode_changes == 2 && mode_changes == 2);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
