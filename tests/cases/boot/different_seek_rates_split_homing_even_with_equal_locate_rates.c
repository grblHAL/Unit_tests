#include "support/boot_homing_motion_host.h"
static unsigned rate_calls[2];
static void observe_separate_axis_rates(axes_signals_t axes, coord_data_t *rates, homing_mode_t mode)
{
    CHECK(axes.mask == X_AXIS_BIT || axes.mask == Y_AXIS_BIT);
    unsigned axis = axes.mask == X_AXIS_BIT ? X_AXIS : Y_AXIS;
    rate_calls[axis]++;
    NEAR(rates->values[axis], mode == HomingMode_Locate ? 25 : (axis == X_AXIS ? 100 : 200));
}
static void install_separate_seek_rates(void)
{
    install_boot_homing_driver();
    settings.homing.flags.per_axis_feedrates = true;
    memset(settings.homing.cycle, 0, sizeof(settings.homing.cycle));
    settings.homing.cycle[0].mask = X_AXIS_BIT | Y_AXIS_BIT;
    settings.axis[Y_AXIS].homing_seek_rate = 200;
    settings_write_global();
    grbl.on_homing_rate_set = observe_separate_axis_rates;
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_separate_seek_rates;
    boot_program = "$H\n";
    CHECK(grbl_enter() == 0);
    CHECK(rate_calls[X_AXIS] == 4 && rate_calls[Y_AXIS] == 4);
    CHECK(boot_motor_position[X_AXIS] == 70 && boot_motor_position[Y_AXIS] == 110);
    CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_pulses[Y_AXIS] == 150);
    CHECK(boot_motor_pulses[Z_AXIS] == 0);
    CHECK(sys.homed.mask == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
