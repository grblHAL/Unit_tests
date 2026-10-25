#include "support/boot_stream_motion_host.h"

static char parking_program[256];
static bool disabled_before_end, door_opened, resume_sent;
static unsigned parked_polls, z_before_parking;
static int32_t z_before_position;

static void add_door_capability(settings_t *current)
{
    CHECK(current == &settings);
    hal.signals_cap.safety_door_ajar = true;
}
static void observe_sender(void)
{
    if(strncmp(boot_program + boot_reads, "M2\n", 3) == 0) {
        CHECK(gc_state.modal.override_ctrl.parking_disable && sys.override.control.parking_disable);
        CHECK(settings.parking.flags.enabled && settings.parking.flags.enable_override_control);
        CHECK(!settings.parking.flags.deactivate_upon_init);
        disabled_before_end = true;
    }
}
static void service_parking(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state == STATE_SAFETY_DOOR && boot_homing_timer_running)
        stepper_driver_interrupt_handler();
    if(!door_opened && state == STATE_CYCLE && sys.position[X_AXIS] >= 40) {
        CHECK(disabled_before_end && sys.homed.mask == Z_AXIS_BIT);
        CHECK(!gc_state.modal.override_ctrl.parking_disable && !sys.override.control.parking_disable);
        CHECK(sys.position[Z_AXIS] == -800);
        z_before_parking = boot_motor_pulses[Z_AXIS];
        z_before_position = boot_motor_position[Z_AXIS];
        boot_control_signals.safety_door_ajar = true;
        hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true});
        door_opened = true;
    }
    if(door_opened && !resume_sent && sys.parking_state == Parking_DoorAjar) {
        CHECK(state_get() == STATE_SAFETY_DOOR && sys.position[Z_AXIS] == -160);
        CHECK(boot_motor_position[Z_AXIS] == z_before_position + 640);
        CHECK(boot_motor_pulses[Z_AXIS] - z_before_parking == 640);
        CHECK(sys.position[X_AXIS] > 0 && sys.position[X_AXIS] < 160);
        if(++parked_polls == 4) {
            boot_control_signals.safety_door_ajar = false;
            hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true, .deasserted = true});
            CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
            resume_sent = true;
        }
    }
}
static void install_parking_driver(void)
{
    install_boot_motion_driver();
    grbl.on_execute_delay = service_parking;
}

int main(void)
{
    snprintf(parking_program, sizeof(parking_program),
        "$22=3\n$HZ\n$%u=5\n$%u=2\n$%u=2\n$%u=100\n$%u=-2\n$%u=500\n"
        "G90G0Z-10\nM56P0\nM2\nG1X2F100\n$G\n",
        (unsigned)Setting_ParkingEnable, (unsigned)Setting_ParkingAxis,
        (unsigned)Setting_ParkingPulloutIncrement, (unsigned)Setting_ParkingPulloutRate,
        (unsigned)Setting_ParkingTarget, (unsigned)Setting_ParkingFastRate);
    prepare_boot_stream_motion(parking_program);
    boot_during_setup = add_door_capability;
    boot_during_init = install_parking_driver;
    boot_before_read = observe_sender;
    boot_on_realtime = service_parking;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(disabled_before_end && door_opened && resume_sent && parked_polls == 4);
    CHECK(boot_motor_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(boot_motor_pulses[X_AXIS] == 160 && boot_motor_pulses[Y_AXIS] == 0);
    CHECK(sys.position[Z_AXIS] == -800 && boot_motor_position[Z_AXIS] == z_before_position);
    CHECK(boot_motor_pulses[Z_AXIS] - z_before_parking == 1280);
    CHECK(!sys.override.control.parking_disable && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
