#include "support/boot_host.h"
#include "spindle_control.h"

static spindle_state_t pwm_states[2];
static unsigned pwm_outputs[2];
static bool primary_ran, startup_checked;
static void boot_pwm_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    unsigned id = (unsigned)spindle->id;
    pwm_states[id] = state;
    pwm_outputs[id]++;
    if(id == 1) {
        CHECK(!state.on);
        NEAR(rpm, 0);
        startup_checked = true;
    } else if(state.on) {
        CHECK(startup_checked && pwm_outputs[1] == 1);
        primary_ran = true;
        NEAR(rpm, 3000);
    }
}
static spindle_state_t boot_pwm_state(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    return pwm_states[spindle->id];
}
static void register_optional_configuration_pwms(void)
{
    static spindle_pwm_t pwm[2];
    static spindle_pwm_settings_t pwm_settings = {
        .rpm_min = 0, .rpm_max = 12000, .pwm_freq = 1000, .pwm_max_value = 100
    };
    static spindle_ptrs_t drivers[] = {
        {.type = SpindleType_PWM, .ref_id = 10, .rpm_min = 0, .rpm_max = 12000,
         .cap = {.variable = true, .rpm_range_locked = true},
         .set_state = boot_pwm_output, .get_state = boot_pwm_state},
        {.type = SpindleType_PWM, .ref_id = 20, .rpm_min = 0, .rpm_max = 12000,
         .cap = {.variable = true, .rpm_range_locked = true},
         .set_state = boot_pwm_output, .get_state = boot_pwm_state}
    };
    for(unsigned i = 0; i < 2; i++) {
        CHECK(spindle_precompute_pwm_values(&drivers[i], &pwm[i], &pwm_settings, 1000000));
        spindle_update_caps(&drivers[i], &pwm[i]);
    }
    CHECK(spindle_register(&drivers[0], "Primary PWM") == 0);
    CHECK(spindle_register(&drivers[1], "Additional PWM") == 1);
}

int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = register_optional_configuration_pwms;
    boot_program = "M3S3000\nM5\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(startup_checked && primary_ran);
    CHECK(pwm_outputs[0] >= 3 && pwm_outputs[1] == 1);
    CHECK(!pwm_states[0].on && !pwm_states[1].on);
    CHECK(spindle_get_count() == 2 && spindle_get_default() == 0);
    CHECK(spindle_is_enabled(0) && !spindle_is_enabled(1));
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "Fatal:") == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    return EXIT_SUCCESS;
}
