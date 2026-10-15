#pragma once
#include "support/boot_stream_motion_host.h"
static char boot_rtcp_program[512];
static inline void prepare_zero_center_rtcp_stream_motion(const char *commands)
{
    size_t used = 0;
    for(unsigned offset = 0; offset < 6; offset++) {
        int length = snprintf(boot_rtcp_program + used, sizeof(boot_rtcp_program) - used,
            "$%u=0\n", (unsigned)(Setting_Kinematics0 + offset));
        CHECK(length > 0 && (size_t)length < sizeof(boot_rtcp_program) - used);
        used += (size_t)length;
    }
    int length = snprintf(boot_rtcp_program + used, sizeof(boot_rtcp_program) - used,
        "$%u=3\n%s", (unsigned)Settings_RotaryAxes, commands);
    CHECK(length > 0 && (size_t)length < sizeof(boot_rtcp_program) - used);
    boot_motion_physical_nvs = true;
    prepare_boot_stream_motion(boot_rtcp_program);
}
