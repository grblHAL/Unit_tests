#include "support/three_pwm_program_host.h"

int main(void)
{
    prepare_three_pwm_program();
    spindle_ptrs_t *configured = triple_configured[1];
    CHECK(configured != NULL && configured->id == 1);
    unsigned untouched[3];
    for(unsigned id = 0; id < 3; id++) untouched[id] = triple_calls[id];
    triple_settings[1].rpm_min = 100;
    triple_settings[1].rpm_max = 8000;
    triple_settings[1].pwm_freq = 500;
    triple_settings[1].pwm_off_value = 5;
    triple_settings[1].flags.pwm_ramped = false;
    triple_settings[1].flags.ignore_delays = true;
    CHECK(spindle_precompute_pwm_values(configured, &triple_pwm[1], &triple_settings[1], 1000000));
    spindle_update_caps(configured, &triple_pwm[1]);
    spindle_ptrs_t *secondary = spindle_get(1);
    NEAR(secondary->rpm_min, 100);
    NEAR(secondary->rpm_max, 8000);
    CHECK(secondary->pwm_off_value == 100);
    CHECK(!secondary->param->option.ramp_up && !secondary->param->option.ramp_down);
    CHECK(secondary->param->option.ignore_delays);
    for(unsigned id = 0; id < 3; id++) {
        CHECK(triple_calls[id] == untouched[id]);
        if(id != 1) {
            spindle_ptrs_t *other = spindle_get(id);
            NEAR(other->rpm_min, 0);
            NEAR(other->rpm_max, 10000);
            CHECK(other->pwm_off_value == 0);
            CHECK(other->param->option.ramp_up && other->param->option.ramp_down);
            CHECK(!other->param->option.ignore_delays);
        }
    }
    uint32_t before = engine_ticks;
    CHECK(spindle_program_block("M3S4000$1") == Status_OK);
    CHECK(engine_ticks == before && actual_spindle_states[1].on);
    CHECK(triple_output[1] == triple_get_pwm(secondary, 4000));
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(engine_ticks == before && !actual_spindle_states[1].on);
    CHECK(triple_output[1] == 100);
    triple_settings[1].rpm_min = 0;
    triple_settings[1].rpm_max = 10000;
    triple_settings[1].pwm_freq = 1000;
    triple_settings[1].pwm_off_value = 0;
    triple_settings[1].flags.pwm_ramped = true;
    triple_settings[1].flags.ignore_delays = false;
    CHECK(spindle_precompute_pwm_values(configured, &triple_pwm[1], &triple_settings[1], 1000000));
    spindle_update_caps(configured, &triple_pwm[1]);
    CHECK(secondary->param->option.ramp_up && secondary->param->option.ramp_down);
    CHECK(!secondary->param->option.ignore_delays && secondary->pwm_off_value == 0);
    NEAR(secondary->rpm_min, 0);
    NEAR(secondary->rpm_max, 10000);
    CHECK(spindle_program_block("M3S4000$1") == Status_OK);
    CHECK(engine_ticks > before && actual_spindle_states[1].on);
    CHECK(triple_output[1] == triple_get_pwm(secondary, 4000));
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(!actual_spindle_states[1].on && triple_output[1] == 0);
    CHECK(triple_calls[0] == untouched[0] && triple_calls[2] == untouched[2]);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[2].on);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
