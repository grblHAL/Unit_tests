#include "support/stepper_host.h"
#include "support/user_mcode_host.h"
#include "check.h"
static unsigned pump_ticks;
static void pump_user_motion(sys_state_t state)
{
    CHECK(user_execute_calls == 0);
    CHECK(++pump_ticks < 100000);
    if(state == STATE_CYCLE) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}

int main(void)
{
    prepare_stepper();
    install_user_mcodes();
    user_synchronized = true;
    grbl.on_execute_realtime = pump_user_motion;
    float target[N_AXIS] = {1.0f};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    CHECK(mc_line(target, &data) == Status_Handled);
    CHECK(plan_get_current_block() != NULL);
    CHECK(user_mcode_block("M400") == Status_OK);
    CHECK(user_execute_calls == 1);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
