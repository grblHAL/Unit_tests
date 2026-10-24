#include "support/boot_stream_motion_host.h"

static bool start_sent, pendant_disabled;
static enqueue_realtime_command_ptr pendant_handler = stream_mpg_check_enable;
static int32_t read_pendant(void) { return SERIAL_NO_DATA; }
static bool disable_pendant(bool disabled) { pendant_disabled = disabled; return true; }
static void write_pendant(const char *text) { (void)text; }
static enqueue_realtime_command_ptr set_pendant_handler(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = pendant_handler; if(handler) pendant_handler = handler; return previous; }
static void service_cut_with_pendant(sys_state_t state)
{
    boot_motion_foreground(state);
    if(!start_sent && state_get() == STATE_CYCLE && boot_motor_pulses[X_AXIS] >= 8) {
        CHECK(boot_motor_pulses[X_AXIS] < 160 && plan_get_current_block() != NULL);
        CHECK(!pendant_disabled && !sys.mpg_mode);
        CHECK(!hal.stream.report.flags.cycle_start);
        CHECK(pendant_handler(CMD_CYCLE_START));
        CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
        CHECK(!hal.stream.report.flags.cycle_start);
        CHECK(pendant_handler(CMD_CYCLE_START_LEGACY));
        CHECK(!hal.stream.report.flags.cycle_start);
        CHECK(hal.stream.read == read_char && state_get() == STATE_CYCLE);
        start_sent = true;
    }
}
static void install_pendant_motion_driver(void)
{
    install_boot_motion_driver();
    settings.status_report.pin_state = true;
    settings_write_global();
    static const io_stream_t pendant = {.type = StreamType_Serial, .instance = 1,
        .read = read_pendant, .write = write_pendant, .is_connected = connected,
        .reset_read_buffer = reset_read, .disable_rx = disable_pendant,
        .set_enqueue_rt_handler = set_pendant_handler};
    CHECK(stream_mpg_register(&pendant, false, stream_mpg_check_enable));
    grbl.on_execute_delay = service_cut_with_pendant;
}
int main(void)
{
    prepare_boot_stream_motion("G1X2F100\n");
    boot_during_init = install_pendant_motion_driver;
    boot_on_realtime = service_cut_with_pendant;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(start_sent && boot_motor_pulses[X_AXIS] == 160);
    CHECK(boot_motor_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(!sys.mpg_mode && hal.stream.read == read_char);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
