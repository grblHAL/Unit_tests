#include "support/boot_homing_motion_host.h"
static void install_rotary_homing_driver(void)
{
    install_boot_homing_driver();
    settings.steppers.is_rotary.mask = 1u << A_AXIS;
    settings.axis[A_AXIS].max_travel = 0;
    settings_write_global();
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_rotary_homing_driver;
    boot_program = "$HA\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == (1u << A_AXIS));
    CHECK(boot_motor_pulses[A_AXIS] == 230 && boot_motor_position[A_AXIS] == 190);
    CHECK(sys.position[A_AXIS] == -10);
    NEAR(gc_state.position[A_AXIS], -.125f);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != A_AXIS) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
