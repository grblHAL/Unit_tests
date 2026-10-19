#pragma once
#include "support/boot_spindle_setup_host.h"
static bool gpio_spindle_direction;
static void register_gpio_spindle_during_init(void)
{
    setup_spindles[0] = (spindle_ptrs_t){.type = SpindleType_Basic, .ref_id = 10,
        .rpm_min = 1000, .rpm_max = 12000,
        .cap = {.enable = true, .direction = gpio_spindle_direction,
            .gpio_controlled = true, .rpm_range_locked = true},
        .config = configure_setup_spindle, .set_state = output_setup_spindle,
        .get_state = state_setup_spindle};
    CHECK(spindle_register(&setup_spindles[0], "GPIO spindle") == 0);
}
static inline void run_gpio_spindle_options(bool direction)
{
    gpio_spindle_direction = direction;
    boot_spindle_reference = 10;
    boot_during_init = register_gpio_spindle_during_init;
    boot_program = direction ? "$16=3\n$16\n" : "$16=1\n$16\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(setup_spindle_configurations[0] > 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, direction ? "$16=3" ASCII_EOL : "$16=1" ASCII_EOL) != NULL);
    CHECK(settings.pwm_spindle.invert.mask == (direction ? 3 : 1));
    const setting_detail_t *option = setting_get_details(Setting_SpindleInvertMask, NULL);
    CHECK(option != NULL);
    CHECK(strcmp(option->format, direction ? "Spindle enable,Spindle direction" : "Spindle enable") == 0);
}
