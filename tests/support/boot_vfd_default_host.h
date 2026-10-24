#pragma once
#include "support/boot_host.h"
#include "spindle_control.h"
static spindle_ptrs_t default_boot_drivers[2];
static spindle_pwm_t unused_pwm_context;
static unsigned default_boot_configs[2], default_boot_outputs[2];
static float unused_pwm_minimum, unused_pwm_maximum;
static bool unused_pwm_locked, unused_pwm_unavailable;
static bool configure_default_boot_spindle(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    default_boot_configs[spindle->id]++;
    if(spindle->id == 1) CHECK(unused_pwm_unavailable ? default_boot_outputs[0] == 0 : default_boot_outputs[0] > 0);
    if(spindle->id == 0) {
        unused_pwm_minimum = spindle->rpm_min;
        unused_pwm_maximum = spindle->rpm_max;
    }
    return spindle->id != 0 || !unused_pwm_unavailable;
}
static void default_boot_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    CHECK(!state.on && rpm == 0);
    default_boot_outputs[spindle->id]++;
}
static spindle_state_t default_boot_input(spindle_ptrs_t *spindle)
{
    (void)spindle;
    return (spindle_state_t){0};
}
static uint_fast16_t unused_pwm_value(spindle_ptrs_t *spindle, float rpm)
{
    (void)spindle;
    CHECK(rpm == 0);
    return 0;
}
static void unused_pwm_update(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{
    (void)spindle;
    CHECK(pwm == 0);
}
static void default_vfd_update(spindle_ptrs_t *spindle, float rpm)
{
    CHECK(spindle->id == 1 && rpm == 0);
}
static void register_unused_pwm_during_init(void)
{
    /* Preload the machine's persisted PWM settings before settings_init. */
    settings.pwm_spindle.rpm_min = 200;
    settings.pwm_spindle.rpm_max = 24000;
    settings_write_global();
    unused_pwm_context.settings = &settings.pwm_spindle;
    default_boot_drivers[0] = (spindle_ptrs_t){.type = SpindleType_PWM, .ref_id = 10,
        .context = {.pwm = &unused_pwm_context}, .rpm_min = 100, .rpm_max = 12000,
        .cap = {.enable = true, .variable = true, .rpm_range_locked = unused_pwm_locked},
        .config = configure_default_boot_spindle, .set_state = default_boot_output,
        .get_state = default_boot_input, .get_pwm = unused_pwm_value, .update_pwm = unused_pwm_update};
    CHECK(spindle_register(&default_boot_drivers[0], "PWM") == 0);
}
static void register_default_vfd_during_setup(settings_t *current)
{
    CHECK(current == &settings && sys.ioinit_pending);
    default_boot_drivers[1] = (spindle_ptrs_t){.type = SpindleType_VFD, .ref_id = 20,
        .rpm_min = 500, .rpm_max = 18000,
        .cap = {.enable = true, .variable = true, .rpm_range_locked = true},
        .config = configure_default_boot_spindle, .set_state = default_boot_output,
        .get_state = default_boot_input, .update_rpm = default_vfd_update};
    CHECK(spindle_register(&default_boot_drivers[1], "VFD") == 1);
}
static void run_vfd_default_boot(bool locked)
{
    unused_pwm_locked = locked;
    boot_spindle_reference = 20;
    boot_during_init = register_unused_pwm_during_init;
    boot_during_setup = register_default_vfd_during_setup;
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(spindle_get(0)->id == 1 && settings.spindle.ref_id == 20);
    CHECK(default_boot_configs[0] == 1 && default_boot_configs[1] == 1);
    CHECK(unused_pwm_unavailable ? default_boot_outputs[0] == 0 : default_boot_outputs[0] >= 1);
    CHECK(default_boot_outputs[1] >= 1);
    NEAR(unused_pwm_minimum, locked ? 100 : 200);
    NEAR(unused_pwm_maximum, locked ? 12000 : 24000);
    CHECK(strstr(engine_output, "[GC:") != NULL);
}
