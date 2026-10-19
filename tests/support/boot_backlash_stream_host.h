#pragma once
#include "support/boot_stream_motion_host.h"
static char backlash_stream_program[2048];
static bool backlash_start_negative;
static inline void prepare_backlash_stream(unsigned axis, bool reverse)
{
    CHECK(axis < 3);
    int used = snprintf(backlash_stream_program, sizeof(backlash_stream_program),
        "$%u=0.1\nG91\n", (unsigned)Setting_AxisBacklash + axis);
    CHECK(used > 0);
    for(unsigned line = 0; line < 40; line++) {
        size_t remaining = sizeof(backlash_stream_program) - (size_t)used;
        int added = snprintf(backlash_stream_program + used, remaining,
            "G1%c%s1F100\n", "XYZ"[axis], ((reverse && (line & 1)) != backlash_start_negative) ? "-" : "");
        CHECK(added > 0 && (size_t)added < remaining);
        used += added;
    }
    prepare_boot_stream_motion(backlash_stream_program);
}
static inline void check_backlash_stream(unsigned axis, bool reverse)
{
    check_boot_motion_completion();
    CHECK(boot_motion_full_planner_seen && boot_motion_before_ack);
    NEAR(settings.axis[axis].backlash, .1f);
    for(unsigned motor = 0; motor < N_AXIS; motor++) {
        int32_t logical = motor == axis && !reverse ? (backlash_start_negative ? -3200 : 3200) : 0;
        int32_t physical = logical;
        unsigned pulses = 0;
        if(motor == axis) {
            // Default homing direction initializes take-up toward negative motion.
            unsigned take_ups = reverse ? (backlash_start_negative ? 39 : 40) : (backlash_start_negative ? 0 : 1);
            pulses = 3200 + 8 * take_ups;
            physical += reverse ? (backlash_start_negative ? 8 : 0) : (backlash_start_negative ? 0 : 8);
        }
        CHECK(sys.position[motor] == logical);
        CHECK(boot_motor_position[motor] == physical);
        CHECK(boot_motor_pulses[motor] == pulses);
    }
}
