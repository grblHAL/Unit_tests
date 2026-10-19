#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    /* A virtual machine with an already homed auxiliary axis and no XYZ limits. */
    settings.homing.flags.enabled = true;
    settings.limits.soft_enabled.mask = sys.soft_limits.mask = sys.homed.mask = 1u << A_AXIS;
    sys.work_envelope.min.values[A_AXIS] = -2;
    sys.work_envelope.max.values[A_AXIS] = 2;
    queue_motion_program("G3X1Y1A1J1F100");
    execute_motion_program();
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        int32_t expected = axis == X_AXIS || axis == Y_AXIS || axis == A_AXIS ? 80 : 0;
        CHECK(sys.position[axis] == expected && physical_position[axis] == expected);
        CHECK(axis_pulses[axis] == (unsigned)expected);
    }
    CHECK(!sys.flags.soft_limit && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
