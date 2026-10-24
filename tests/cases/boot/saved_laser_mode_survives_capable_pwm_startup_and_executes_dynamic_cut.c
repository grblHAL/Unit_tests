#include "support/boot_stream_motion_host.h"
#include "support/laser_program_host.h"

static void install_boot_laser(void)
{
    install_boot_motion_driver();
    settings.mode = Mode_Laser;
    settings.spindle.ref_id = 10;
    laser_pwm_context.settings = &settings.pwm_spindle;
    laser_driver = (spindle_ptrs_t){.type = SpindleType_PWM, .ref_id = 10,
        .context = {.pwm = &laser_pwm_context}, .rpm_min = 0, .rpm_max = 1000,
        .cap = {.enable = true, .variable = true, .direction = true,
            .laser = true, .rpm_range_locked = true},
        .set_state = laser_output, .get_state = laser_input,
        .get_pwm = laser_get_pwm, .update_pwm = laser_update_pwm};
    CHECK(spindle_register(&laser_driver, "PWM laser") == 0);
    settings_write_global();
}

static void check_live_laser_startup(void)
{
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    CHECK(settings.mode == Mode_Laser && spindle_get(0)->cap.laser);
}

int main(void)
{
    prepare_boot_stream_motion("G1M4S500F100X1\nM5\n$32\n$G\n");
    boot_during_init = install_boot_laser;
    boot_before_read = check_live_laser_startup;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(settings.mode == Mode_Laser && spindle_get(0)->cap.laser);
    CHECK(strstr(engine_output, "$32=1" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL && strstr(engine_output, " M5") != NULL);
    CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    bool powered_during_cut = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++)
        powered_during_cut |= laser_pwm_log[i] > 0;
    CHECK(powered_during_cut && !laser_output_state.on && laser_last_driver_level == 0);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
