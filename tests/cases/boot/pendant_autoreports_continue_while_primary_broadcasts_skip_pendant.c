#include "support/boot_host.h"

static char pendant_output[2048];
static io_stream_t primary_device;
static unsigned service_calls;
static bool finished;
static enqueue_realtime_command_ptr primary_handler = protocol_enqueue_realtime_command;
static enqueue_realtime_command_ptr pendant_handler = stream_mpg_check_enable;
static enqueue_realtime_command_ptr set_primary_handler(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = primary_handler; if(handler) primary_handler = handler; return previous; }
static enqueue_realtime_command_ptr set_pendant_handler(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = pendant_handler; if(handler) pendant_handler = handler; return previous; }
static int32_t read_pendant(void) { return SERIAL_NO_DATA; }
static bool disable_pendant(bool disabled) { (void)disabled; return true; }
static void write_pendant(const char *text)
{
    CHECK(strlen(pendant_output) + strlen(text) < sizeof(pendant_output));
    strcat(pendant_output, text);
}
static void register_pendant(void)
{
    primary_device = hal.stream;
    primary_device.type = StreamType_Serial;
    primary_device.set_enqueue_rt_handler = set_primary_handler;
    CHECK(stream_connect(&primary_device));
    static const io_stream_t pendant = {.type = StreamType_Serial, .instance = 1,
        .read = read_pendant, .write = write_pendant, .is_connected = connected,
        .reset_read_buffer = reset_read, .disable_rx = disable_pendant,
        .set_enqueue_rt_handler = set_pendant_handler};
    CHECK(stream_mpg_register(&pendant, false, NULL));
    hal.driver_cap.mpg_mode = true;
}
static void configure_pendant_reports(settings_t *current)
{
    CHECK(current == &settings);
    char interval[] = "100";
    CHECK(settings_store_setting(Setting_MPGAutoReportInterval, interval) == Status_OK);
}
static void service_pendant_reports(sys_state_t state)
{
    CHECK(++service_calls < 200);
    CHECK(state == STATE_IDLE);
    engine_ticks += 50;
    const char *first = strstr(pendant_output, "<Idle|");
    if(!finished && first && strstr(first + 1, "<Idle|")) {
        CHECK(sys.flags.mpg_auto_reporting && !sys.mpg_mode);
        size_t before = strlen(pendant_output);
        hal.stream.write_all("primary broadcast\n");
        CHECK(strstr(engine_output, "primary broadcast\n") != NULL);
        CHECK(strlen(pendant_output) == before);
        CHECK(hal.stream.read == read_char);
        finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
int main(void)
{
    boot_during_init = register_pendant;
    boot_during_setup = configure_pendant_reports;
    boot_on_realtime = service_pendant_reports;
    boot_observe_fault_loop = true;
    CHECK(grbl_enter() == 0);
    CHECK(finished && settings.mpg_report_interval == 100);
    CHECK(!sys.mpg_mode && hal.stream.read == read_char);
    CHECK(strstr(pendant_output, "primary broadcast") == NULL);
    CHECK(strstr(engine_output, "error:") == NULL && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
