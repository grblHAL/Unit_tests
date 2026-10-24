#include "support/boot_stream_motion_host.h"

static char reset_program[160];
static bool homing_observed, reset_sent, restart_observed;
static int32_t z_at_reset, z_at_restart;
static unsigned homing_pulses, pulses_at_restart;

static void observe_reset_startup(void)
{
    if(!homing_observed && sys.homed.mask == Z_AXIS_BIT && state_get() == STATE_IDLE) {
        CHECK(sys.homing.mask == Z_AXIS_BIT);
        homing_pulses = boot_motor_pulses[Z_AXIS];
        homing_observed = true;
    }
    const char *welcome = strstr(engine_output, "GrblHAL");
    if(reset_sent && !restart_observed && !sys.abort && welcome && strstr(welcome + 1, "GrblHAL")) {
        CHECK(settings.homing.flags.keep_on_reset && sys.homed.mask == Z_AXIS_BIT);
        z_at_restart = boot_motor_position[Z_AXIS];
        pulses_at_restart = boot_motor_pulses[Z_AXIS];
        restart_observed = true;
    }
}
static int32_t read_reset_sender(void)
{
    observe_reset_startup();
    const char *unlock = strstr(boot_program, "$X");
    CHECK(unlock != NULL);
    if(boot_reads == (unsigned)(unlock - boot_program) && !restart_observed)
        return SERIAL_NO_DATA;
    return read_char();
}
static void service_reset_motion(sys_state_t state)
{
    boot_homing_foreground(state);
    if(!reset_sent && homing_observed && state == STATE_CYCLE && sys.position[Z_AXIS] <= -80) {
        CHECK(sys.position[Z_AXIS] > -800 && settings.homing.flags.keep_on_reset);
        CHECK(sys.homed.mask == Z_AXIS_BIT);
        z_at_reset = sys.position[Z_AXIS];
        reset_sent = true;
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
    if(restart_observed && !boot_motion_exit_queued && boot_reads == strlen(boot_program) &&
       state_get() == STATE_IDLE && plan_get_current_block() == NULL &&
       boot_motion_ack_count() == boot_motion_expected_acks) {
        CHECK(!sys.abort && sys.alarm == Alarm_None);
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_motion_exit_queued = true;
    }
}
static void install_reset_motion_driver(void)
{
    install_boot_motion_driver();
    hal.stream.read = read_reset_sender;
    grbl.on_execute_delay = service_reset_motion;
}

int main(void)
{
    snprintf(reset_program, sizeof(reset_program),
        "$22=3\n$%u=4\n$%u=14\n$HZ\nG1Z-10F100\n$X\n$G\n",
        (unsigned)Setting_HomingCycle_1, (unsigned)Setting_ResetActions);
    prepare_boot_stream_motion(reset_program);
    boot_during_init = install_reset_motion_driver;
    boot_on_realtime = service_reset_motion;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(homing_observed && reset_sent && restart_observed);
    CHECK(sys.homed.mask == Z_AXIS_BIT && settings.homing.flags.keep_on_reset);
    CHECK(sys.position[Z_AXIS] <= -80 && sys.position[Z_AXIS] > -800);
    CHECK(sys.position[Z_AXIS] == z_at_reset);
    CHECK(boot_motor_position[Z_AXIS] == z_at_restart && boot_motor_pulses[Z_AXIS] == pulses_at_restart);
    CHECK(pulses_at_restart > homing_pulses && pulses_at_restart - homing_pulses < 790);
    CHECK(boot_motor_pulses[X_AXIS] == 0 && boot_motor_pulses[Y_AXIS] == 0);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
