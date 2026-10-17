#pragma once
#include "support/boot_homing_motion_host.h"
#include "support/boot_spindle_setup_host.h"
static bool saw_accessories_on, saw_homing;
static bool router_report_progress = true;
static void observe_accessories_before_home(void)
{
    if(boot_reads == sizeof("M3S5000\nM8\n") - 1) {
        CHECK(setup_spindle_states[0].on && boot_coolant_state.flood);
        saw_accessories_on = true;
    }
}
static void verify_homing_pulse(stepper_t *stepper)
{
    if(stepper->step_out.mask) {
        CHECK(saw_accessories_on);
        CHECK(!setup_spindle_states[0].on && boot_coolant_state.mask == 0);
        CHECK(!gc_spindle_get(0)->state.on && gc_state.modal.coolant.mask == 0);
        if(!router_report_progress)
            CHECK(strstr(engine_output, "<Home|") != NULL);
        saw_homing = true;
    }
    boot_homing_pulse(stepper);
}
static void install_router_homing_driver(void)
{
    install_boot_homing_driver();
    register_primary_during_init();
    hal.coolant_cap.flood = true;
    settings.homing.flags.enabled = true;
    settings.homing.flags.init_lock = false;
    settings.homing.cycle[0].mask = AXES_BITMASK;
    settings.status_report.when_homing = router_report_progress;
    settings_write_global();
    hal.stepper.pulse_start = verify_homing_pulse;
}
static inline void run_router_homing(void)
{
    boot_during_init = install_router_homing_driver;
    boot_on_realtime = boot_homing_foreground;
    boot_before_read = observe_accessories_before_home;
    boot_spindle_reference = 10;
    boot_program = "M3S5000\nM8\n$HX\n";
    CHECK(grbl_enter() == 0);
    CHECK(saw_accessories_on && saw_homing);
    CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_position[X_AXIS] == 70);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(strstr(engine_output, "error:") == NULL);
}
