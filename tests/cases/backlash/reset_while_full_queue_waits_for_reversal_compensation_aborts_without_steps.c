#include "support/backlash_host.h"
#include "protocol.h"

static control_signals_t controls(void) { return (control_signals_t){0}; }
static void coolant_off(coolant_state_t state) { CHECK(state.value == 0); }
static void driver_reset(void) {}
static unsigned realtime_calls;
static void reset_during_compensation_wait(sys_state_t state)
{
    (void)state;
    if(++realtime_calls == 2)
        protocol_enqueue_realtime_command(CMD_RESET);
    CHECK(realtime_calls < 10);
}

int main(void)
{
    prepare_backlash();
    hal.control.get_state = controls;
    hal.coolant.set_state = coolant_off;
    hal.driver_reset = driver_reset;
    queue_motion_program("G1X1F100");
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    float target[N_AXIS] = {2};
    unsigned added = 0;
    while(!plan_check_full_buffer()) {
        CHECK(plan_buffer_line(target, &data));
        target[X_AXIS]++;
        CHECK(++added < 100);
    }
    plan_block_t *last = plan_get_recent_block();
    CHECK(last != NULL);
    grbl.on_execute_realtime = reset_during_compensation_wait;
    target[X_AXIS] = 0;
    CHECK(mc_line(target, &data) == Status_Aborted);
    CHECK(realtime_calls >= 2 && sys.abort);
    CHECK(plan_get_recent_block() != NULL);
    CHECK(plan_get_recent_block()->target_mm[X_AXIS] > 0);
    CHECK(sys.position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
