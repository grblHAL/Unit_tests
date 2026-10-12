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
    CHECK(ramp_calls == 0);
    CHECK(rpm_update_calls == 0);
    engine_ticks = 49;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_calls == 0);
    for(unsigned tick = 50; tick <= 1000; tick += 50) {
        engine_ticks = tick;
        engine_execute_tasks(STATE_IDLE);
    }
    CHECK(ramp_calls > 1);
    CHECK(ramp_values[ramp_calls - 1] == 6000);
    for(unsigned i = 1; i < ramp_calls; i++) CHECK(ramp_values[i] >= ramp_values[i-1]);
    CHECK(ramp_values[0] > 5000);
    CHECK(ramp_values[0] < 6000);
    unsigned completed_calls = ramp_calls;
    engine_ticks = 2000;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_calls == completed_calls);
    return EXIT_SUCCESS;
}
