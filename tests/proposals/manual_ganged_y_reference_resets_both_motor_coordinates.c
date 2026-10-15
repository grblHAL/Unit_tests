#include "support/boot_homing_motion_host.h"
static void install_manual_reference_driver(void)
{
    install_boot_homing_driver();
    settings.homing.flags.manual = true;
    settings.homing.flags.force_set_origin = true;
    for(unsigned phase = 0; phase < N_AXIS; phase++) settings.homing.cycle[phase].mask = 0;
    settings_write_global();
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_manual_reference_driver;
    boot_restore_position = true;
    boot_hardware_position[0] = 160;
    boot_hardware_position[1] = -240;
    boot_hardware_position[2] = 320;
    boot_hardware_position[3] = -240;
    boot_program = "$HY\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_position_calls == 1 && sys.homed.mask == Y_AXIS_BIT);
    fprintf(stderr, "Manual Y reference counters: X=%ld Y=%ld Z=%ld secondary=%ld; homed=%u; wakes=%u\n",
        (long)sys.position[0], (long)sys.position[1], (long)sys.position[2], (long)sys.position[3],
        (unsigned)sys.homed.mask, boot_wake_calls);
    CHECK(sys.position[0] == 160 && sys.position[1] == 0);
    CHECK(sys.position[2] == 320 && sys.position[3] == 0);
    NEAR(gc_state.position[0], 2);
    NEAR(gc_state.position[1], 0);
    NEAR(gc_state.position[2], 4);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(boot_wake_calls == 0 && strstr(engine_output, "ALARM:18") == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
