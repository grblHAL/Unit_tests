#include "support/rotary_limit_settings_host.h"
#include "state_machine.h"
static control_signals_t limit_controls(void) { return (control_signals_t){0}; }
int main(void)
{
    prepare_rotary_limit_settings();
    hal.control.get_state = limit_controls;
    state_set(STATE_IDLE);
    CHECK(store_setting(Setting_HardLimitsEnable, "5") == Status_OK);
    CHECK(settings.limits.flags.hard_enabled && settings.limits.flags.hard_disabled_rotary);
    CHECK(!settings.limits.flags.check_at_init);
    CHECK(sys.hard_limits.mask == 215 && rotary_limit_driver_enabled);
    const setting_detail_t *detail = setting_get_details(Setting_HardLimitsEnable, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 5);
    CHECK(rotary_limit_driver_calls == 1 && change_callbacks == 1);
    limit_signals_t previous = sys.last_event.limits;
    sys_state_t previous_state = state_get();
    rt_exec_t previous_exec = sys.rt_exec_state;
    alarm_code_t previous_alarm = sys.rt_exec_alarm;
    bool previous_abort = sys.abort;
    limit_interrupt_handler((limit_signals_t){0});
    limit_interrupt_handler((limit_signals_t){.min.mask = 40});
    limit_interrupt_handler((limit_signals_t){.max.mask = 40});
    CHECK(memcmp(&sys.last_event.limits, &previous, sizeof(previous)) == 0);
    CHECK(state_get() == previous_state);
    CHECK(sys.rt_exec_state == previous_exec && sys.rt_exec_alarm == previous_alarm);
    CHECK(sys.abort == previous_abort);
    CHECK(sys.hard_limits.mask == 215 && rotary_limit_driver_enabled);
    CHECK(state_get() == STATE_IDLE);
    limit_interrupt_handler((limit_signals_t){.min.mask = 1u << X_AXIS});
    CHECK(sys.last_event.limits.min.mask == (1u << X_AXIS));
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(sys.rt_exec_alarm == Alarm_HardLimit);
    CHECK(!sys.position_lost);
    return EXIT_SUCCESS;
}
