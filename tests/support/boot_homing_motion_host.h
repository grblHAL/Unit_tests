#pragma once
#include "support/boot_host.h"
#include "stepper.h"
static int32_t boot_motor_position[N_AXIS];
static unsigned boot_motor_pulses[N_AXIS], boot_wake_calls, boot_homing_service_calls;
static bool boot_homing_timer_running;
static void boot_homing_wake(void) { boot_homing_timer_running = true; boot_wake_calls++; }
static void boot_homing_idle(bool clear) { boot_homing_timer_running = false; idle(clear); }
static void boot_homing_pulse(stepper_t *stepper)
{
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(stepper->step_out.mask & (1u << axis)) {
            boot_motor_pulses[axis]++;
            boot_motor_position[axis] += (stepper->dir_out.mask & (1u << axis)) ? -1 : 1;
        }
}
static home_signals_t boot_homing_switches(void)
{
    home_signals_t state = {0};
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(boot_motor_position[axis] >= 80 + (int32_t)axis * 40)
            state.a.mask |= (1u << axis);
    return state;
}
static void boot_homing_foreground(sys_state_t state)
{
    CHECK(++boot_homing_service_calls < 200000);
    engine_ticks++;
    if(boot_homing_timer_running && (state == STATE_HOMING || state == STATE_CYCLE))
        stepper_driver_interrupt_handler();
}
static void configure_boot_homing(settings_t *current);
static void install_boot_homing_driver(void)
{
    configure_boot_homing(&settings);
    settings_write_global();
    hal.stepper.wake_up = boot_homing_wake;
    hal.stepper.go_idle = boot_homing_idle;
    hal.stepper.pulse_start = boot_homing_pulse;
    hal.homing.get_state = boot_homing_switches;
    hal.home_cap.a.mask = AXES_BITMASK;
    grbl.on_execute_delay = boot_homing_foreground;
}
static void configure_boot_homing(settings_t *current)
{
    CHECK(current == &settings);
    current->homing.flags.single_axis_commands = true;
    current->homing.locate_cycles = 1;
    current->homing.pulloff = .125f;
    current->status_report.when_homing = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        current->axis[axis].homing_seek_rate = 100;
        current->axis[axis].homing_feed_rate = 25;
        current->axis[axis].max_travel = -10;
        current->axis[axis].acceleration = 36000;
    }
}
static inline void prepare_boot_homing_motion(void)
{
    boot_homing_required = true;
    boot_during_init = install_boot_homing_driver;
    boot_on_realtime = boot_homing_foreground;
    boot_program = "$HX\n";
}
