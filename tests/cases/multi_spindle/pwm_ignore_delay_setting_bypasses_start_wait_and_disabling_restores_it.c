#include "support/laser_program_host.h"
static void store_pwm_setting(setting_id_t id, const char *value)
{
    char text[24];
    CHECK(strlen(value) < sizeof(text));
    strcpy(text, value);
    status_code_t status = settings_store_setting(id, text);
    if(status != Status_OK) fprintf(stderr, "setting %u=%s status=%u\n", (unsigned)id, value, (unsigned)status);
    CHECK(status == Status_OK);
}
int main(void)
{
    prepare_pwm_program_mode(Mode_Standard, false);
    store_pwm_setting(Setting_SpindleOnDelay, "0.5");
    store_pwm_setting(Setting_SpindlePWMOptions, "17");
    spindle_update_caps(spindle_get_hal(0, SpindleHAL_Configured), &laser_pwm_context);
    CHECK(spindle_get(0)->param->option.ignore_delays);
    uint32_t before = engine_ticks;
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(engine_ticks == before);
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    NEAR(laser_output_power, 500);
    store_pwm_setting(Setting_SpindlePWMOptions, "1");
    spindle_update_caps(spindle_get_hal(0, SpindleHAL_Configured), &laser_pwm_context);
    CHECK(!spindle_get(0)->param->option.ignore_delays);
    before = engine_ticks;
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(engine_ticks - before == 500);
    CHECK(laser_output_state.on && laser_output_state.ccw);
    NEAR(laser_output_power, 500);
    CHECK(laser_block("M5") == Status_OK);
    CHECK(!laser_output_state.on && state_get() == STATE_IDLE);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
