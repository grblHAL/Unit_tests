#include "support/boot_host.h"

static char pendant_output[4096];
static bool took_control, pendant_disabled;
static unsigned pendant_reads;
static enqueue_realtime_command_ptr primary_handler = protocol_enqueue_realtime_command;
static enqueue_realtime_command_ptr pendant_handler = stream_mpg_check_enable;
static enqueue_realtime_command_ptr set_primary_handler(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = primary_handler; if(handler) primary_handler = handler; return previous; }
static enqueue_realtime_command_ptr set_pendant_handler(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = pendant_handler; if(handler) pendant_handler = handler; return previous; }
static int32_t read_pendant(void) { pendant_reads++; return read_char(); }
static bool disable_pendant(bool disabled) { pendant_disabled = disabled; return true; }
static void write_pendant(const char *text)
{
    CHECK(strlen(pendant_output) + strlen(text) < sizeof(pendant_output));
    strcat(pendant_output, text);
}
static void register_pendant(void)
{
    static const io_stream_t pendant = {.type = StreamType_Serial, .instance = 1,
        .read = read_pendant, .write = write_pendant, .is_connected = connected,
        .reset_read_buffer = reset_read, .disable_rx = disable_pendant,
        .set_enqueue_rt_handler = set_pendant_handler};
    hal.stream.type = StreamType_Serial;
    hal.stream.set_enqueue_rt_handler = set_primary_handler;
    CHECK(stream_mpg_register(&pendant, false, NULL));
    hal.driver_cap.mpg_mode = true;
}
static void take_pendant_control(void)
{
    if(!took_control) {
        CHECK(stream_mpg_enable(true));
        CHECK(sys.mpg_mode && hal.stream.state.is_mpg);
        CHECK(hal.stream.read == read_pendant && !pendant_disabled);
        CHECK(!stream_mpg_enable(true));
        CHECK(sys.mpg_mode && hal.stream.state.is_mpg && !pendant_disabled);
        CHECK(hal.stream.read == read_pendant && pendant_handler == protocol_enqueue_realtime_command);
        took_control = true;
    }
}
int main(void)
{
    boot_during_init = register_pendant;
    boot_before_read = take_pendant_control;
    boot_program = "\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(took_control && pendant_reads > 0 && boot_reads == strlen(boot_program));
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg && !pendant_disabled);
    CHECK(hal.stream.read == read_pendant && pendant_handler == protocol_enqueue_realtime_command);
    CHECK(strstr(pendant_output, "[GC:") != NULL);
    CHECK(strstr(pendant_output, "<Idle|") != NULL);
    CHECK(strstr(pendant_output, "MPG:1") != NULL);
    CHECK(strstr(pendant_output, "|WCS:G54") != NULL);
    CHECK(strstr(pendant_output, "|T:0|P:0|TLR:0|FW:grblHAL") != NULL);
    CHECK(strstr(pendant_output, "error:") == NULL);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
