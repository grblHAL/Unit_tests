#include "support/rotary_limit_settings_host.h"
#include "state_machine.h"
int main(void)
{
    prepare_rotary_limit_settings();
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
    return EXIT_SUCCESS;
}
