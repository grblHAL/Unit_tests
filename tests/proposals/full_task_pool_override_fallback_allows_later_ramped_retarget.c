#include "support/spindle_ramp_host.h"
#include "task.h"

static void pending_plugin_task(void *data) { (void)data; CHECK(false); }

int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active, (spindle_state_t){.on = true}, 6000));
    clear_ramp_records();
    unsigned contexts[64], count = 0;
    while(count < 64 && task_add_delayed(pending_plugin_task, &contexts[count], 1000000))
        count++;
    CHECK(count > 0 && count < 64);
    NEAR(spindle_set_override(active, 150), 9000);
    CHECK(ramp_pwm_calls == 1 && ramp_state_calls == 0);
    CHECK(ramp_pwm_log[0] == active->get_pwm(active, 9000));
    advance_ramp_tasks(2);
    CHECK(ramp_pwm_calls == 1 && ramp_hardware_state.on);
    for(unsigned i = 0; i < count; i++)
        task_delete(pending_plugin_task, &contexts[i]);
    NEAR(spindle_set_override(active, 100), 6000);
    CHECK(ramp_pwm_calls == 1);
    advance_ramp_tasks(1);
    CHECK(ramp_pwm_calls == 2);
    CHECK(ramp_pwm_log[1] < active->get_pwm(active, 9000));
    CHECK(ramp_pwm_log[1] > active->get_pwm(active, 6000));
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_log[ramp_pwm_calls - 1] == active->get_pwm(active, 6000));
    CHECK(ramp_hardware_state.on && ramp_state_calls == 0 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
