#include "support/probe_motion_host.h"

static void stop_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static unsigned driver_resets;
static void reset_driver(void) { driver_resets++; }
static bool reset_sent;
static unsigned probe_starts;
static bool observe_probe_start(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    (void)axes; (void)target; (void)data;
    probe_starts++;
    return true;
}
static void reset_during_cut(sys_state_t state)
{
    execute_foreground(state);
    if(!reset_sent && axis_pulses[X_AXIS] >= 10) {
        reset_sent = true;
        mc_reset();
    }
}

int main(void)
{
    prepare_probe_motion();
    hal.coolant.set_state = stop_coolant;
    hal.driver_reset = reset_driver;
    grbl.on_execute_realtime = reset_during_cut;
    grbl.on_probe_start = observe_probe_start;
    queue_motion_program("G1X1F100");
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Abort);
    CHECK(reset_sent && sys.abort && driver_resets == 1);
    CHECK(axis_pulses[X_AXIS] >= 10 && axis_pulses[X_AXIS] < 80);
    CHECK(probe_starts == 0 && completed_calls == 0);
    CHECK(sys.probing_state == Probing_Off);
    CHECK(!hal.probe.get_state().is_probing);
    CHECK(!sys.flags.probe_succeeded);
    return EXIT_SUCCESS;
}
