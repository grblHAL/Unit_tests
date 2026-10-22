#include "support/homing_host.h"

static bool homing_driver_active;
static void homing_wake(void) { homing_driver_active = true; wake_driver(); }
static void homing_idle(bool clear) { homing_driver_active = false; idle_driver(clear); }
static void service_running_homing(sys_state_t state)
{
    if(homing_driver_active) execute_foreground(state);
}

int main(void)
{
    prepare_homing();
    grbl.on_execute_realtime = grbl.on_execute_delay = service_running_homing;
    hal.stepper.wake_up = homing_wake;
    hal.stepper.go_idle = homing_idle;
    char disabled[] = "0";
    CHECK(settings_store_setting(Setting_AxisMaxTravel, disabled) == Status_OK);
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_OK);
    CHECK(axis_pulses[X_AXIS] == 0 && wake_calls == 0);
    CHECK(!(sys.homed.mask & X_AXIS_BIT));
    CHECK(plan_get_current_block() == NULL);
    char enabled[] = "10";
    CHECK(settings_store_setting(Setting_AxisMaxTravel, enabled) == Status_OK);
    status_code_t retry = mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(retry == Status_OK);
    CHECK(axis_pulses[X_AXIS] > 0 && (sys.homed.mask & X_AXIS_BIT));
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(homing_success && !sys.abort && sys.alarm == Alarm_None);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
