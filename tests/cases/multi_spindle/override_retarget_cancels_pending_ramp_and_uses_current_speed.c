#include "support/spindle_override_host.h"
#include "task.h"
#include "check.h"
static unsigned ramp_calls;
static uint_fast16_t ramp_values[32];
static uint_fast16_t ramp_pwm(spindle_ptrs_t *spindle, float rpm) { CHECK(spindle == spindle_get(0)); return (uint_fast16_t)lroundf(rpm); }
static void ramp_output(spindle_ptrs_t *spindle, uint_fast16_t value) { CHECK(spindle == spindle_get(0)); CHECK(ramp_calls < 32); ramp_values[ramp_calls++] = value; }
int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    spindle->get_pwm = ramp_pwm;
    spindle->update_pwm = ramp_output;
    spindle->param->option.ramp_up = true;
    settings.spindle.on_delay = 2400;
    RPM_NEAR(spindle_set_override(spindle, 120), 6000);
    engine_ticks = 50;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_calls == 1);
    CHECK(ramp_values[0] > 5000 && ramp_values[0] < 6000);
    engine_ticks = 75;
    RPM_NEAR(spindle_set_override(spindle, 80), 4000);
    engine_ticks = 100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_calls == 1);
    for(unsigned tick = 125; tick <= 1000; tick += 50) {
        engine_ticks = tick;
        engine_execute_tasks(STATE_IDLE);
    }
    CHECK(ramp_calls > 2);
    CHECK(ramp_values[1] < ramp_values[0] && ramp_values[1] > 4000);
    for(unsigned i = 1; i < ramp_calls; i++) CHECK(ramp_values[i] <= ramp_values[i-1]);
    CHECK(ramp_values[ramp_calls - 1] == 4000);
    return EXIT_SUCCESS;
}
