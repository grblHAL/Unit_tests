#include "support/probe_motion_host.h"

static unsigned reset_poll_calls, start_calls;
static void coolant_off(coolant_state_t state) { CHECK(state.value == 0); }
static void driver_reset(void) {}
static void reset_before_queue(sys_state_t state)
{
    (void)state;
    CHECK(++reset_poll_calls < 4);
    if(reset_poll_calls == 1)
        protocol_enqueue_realtime_command(CMD_RESET);
}
static bool probe_started(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    CHECK(axes.x && target[X_AXIS] == 1 && data->feed_rate == 100);
    start_calls++;
    grbl.on_execute_realtime = reset_before_queue;
    return true;
}

int main(void)
{
    prepare_probe_motion();
    hal.coolant.set_state = coolant_off;
    hal.driver_reset = driver_reset;
    grbl.on_probe_start = probe_started;
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Abort);
    CHECK(start_calls == 1 && reset_poll_calls == 1);
    CHECK(sys.abort && !sys.flags.probe_succeeded);
    CHECK(axis_pulses[X_AXIS] == 0 && sys.position[X_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    CHECK(completed_calls == 0);
    return EXIT_SUCCESS;
}
