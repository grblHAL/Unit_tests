#pragma once
#include "support/boot_stream_motion_host.h"
static void install_delta_motion_driver(void)
{
    install_boot_motion_driver();
    for(unsigned axis = 0; axis < 3; axis++) {
        settings.axis[axis].steps_per_mm = 1000; /* Delta motors use steps/radian. */
        settings.axis[axis].max_travel = -2;
        settings.axis[axis].max_rate = 10;
    }
    settings_write_global();
}
static inline void prepare_boot_delta_stream_motion(const char *program)
{
    boot_motion_physical_nvs = true;
    prepare_boot_stream_motion(program);
    boot_during_init = install_delta_motion_driver;
}
static inline float delta_zero_angle_height(void)
{
    /* Independent symmetric rod geometry for the stored default dimensions. */
    float radial = 100 + (75 - 24) / (2 * sqrtf(3));
    return -sqrtf(300 * 300 - radial * radial);
}
