#include "support/boot_stream_motion_host.h"

static unsigned held_polls;
static bool resumed;
static void cycle_start_capability(settings_t *current)
{
    CHECK(current == &settings);
    hal.signals_cap.cycle_start = true;
}
static void service_physical_start(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state == STATE_HOLD && sys.holding_state == Hold_Pending)
        stepper_driver_interrupt_handler();
    if(state == STATE_HOLD && sys.holding_state == Hold_Complete && !resumed) {
        CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
        CHECK(boot_motion_ack_count() == 1);
        CHECK(grbl.on_cycle_start == NULL);
        CHECK(grbl.on_control_signals_changed == NULL);
        if(++held_polls == 4) {
            resumed = true;
            boot_control_signals.cycle_start = true;
            hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
            CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
            boot_control_signals.cycle_start = false;
            hal.control.interrupt_callback((control_signals_t){.cycle_start = true, .deasserted = true});
        }
    }
}
static void install_physical_start_driver(void)
{
    install_boot_motion_driver();
    grbl.on_execute_delay = service_physical_start;
}
int main(void)
{
    prepare_boot_stream_motion("G1X1F100\nM0\nG91G1X1F100\n");
    boot_during_setup = cycle_start_capability;
    boot_during_init = install_physical_start_driver;
    boot_on_realtime = service_physical_start;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(resumed && held_polls == 4);
    CHECK(boot_motor_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(boot_motor_pulses[X_AXIS] == 160);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(!boot_control_signals.cycle_start && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
