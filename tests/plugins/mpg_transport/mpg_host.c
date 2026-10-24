#include "mpg_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
io_stream_t proxy;
setting_details_t *registered_settings;
unsigned claims, registrations, rt_calls, resets, warnings, saves, packets, chains;
bool alloc_ok = true, settings_ok = true, claim_ok = true, register_ok = true, baud_ok = true;
uint32_t now, baud;
char output[4096];
struct mpg_packet sent[256];
static enqueue_realtime_command_ptr physical_rx;
static sys_commands_t *commands;
static uint8_t nvs[64];
static size_t stored;
static io_stream_t physical;
static void print(const char *text)
{
    CHECK(strlen(output) + strlen(text) < sizeof(output));
    strcat(output, text);
}
static void transmit(const uint8_t *data, uint16_t size)
{
    CHECK(packets < 256 && size <= 256);
    memcpy(sent[packets].data, data, size);
    sent[packets++].size = size;
}
static bool transmit_char(uint8_t value)
{
    transmit(&value, 1);
    return true;
}
static bool set_baud(uint32_t value)
{
    if (!baud_ok)
        return false;
    baud = value;
    return true;
}
static bool disable_rx(bool disable)
{
    (void)disable;
    CHECK(false);
    return false;
}
static bool connected(void) { return true; }
static uint16_t count_tx(void) { return 0; }
static void reset_tx(void) { chains++; }
static uint32_t ticks(void) { return now; }
static void reset(void) { resets++; }
static void options(bool newopt)
{
    (void)newopt;
    chains++;
}
static void realtime(sys_state_t state)
{
    CHECK(state == STATE_IDLE);
    chains++;
}
bool protocol_enqueue_realtime_command(uint8_t value)
{
    rt_calls++;
    return value == '!';
}
bool stream_mpg_check_enable(uint8_t value) { return protocol_enqueue_realtime_command(value); }
io_stream_t const *stream_open_instance(uint8_t instance, uint32_t rate,
                                        stream_write_char_ptr handler, const char *description)
{
    CHECK(instance == 1 && rate == 115200 && handler && description);
    claims++;
    if (!claim_ok)
        return NULL;
    physical_rx = handler;
    baud = rate;
    return &physical;
}
bool stream_mpg_register(const io_stream_t *stream, bool rx_only, stream_write_char_ptr handler)
{
    CHECK(stream && !rx_only && handler == stream_mpg_check_enable);
    registrations++;
    if (!register_ok)
        return false;
    proxy = *stream;
    CHECK(proxy.set_enqueue_rt_handler);
    proxy.set_enqueue_rt_handler(protocol_enqueue_realtime_command);
    return true;
}
bool stream_set_description(const io_stream_t *stream, const char *description)
{
    CHECK(stream == &physical && description);
    return true;
}
bool stream_rx_suspend(stream_rx_buffer_t *buffer, bool suspend)
{
    (void)buffer;
    (void)suspend;
    CHECK(false);
    return false;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size <= sizeof(nvs));
    return alloc_ok ? 2048 : 0;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t addr, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    if (!stored)
        return false;
    CHECK(size == stored);
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t addr, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return true;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!registered_settings);
    if (!settings_ok)
        return false;
    registered_settings = details;
    return true;
}
void system_register_commands(sys_commands_t *list)
{
    CHECK(!commands);
    commands = list;
}
void report_warning(void *text)
{
    CHECK(text);
    warnings++;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    fn(data);
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    fn(data);
    return true;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "MPG/DRO framed transport") == 0 && strcmp(version, "1.00") == 0);
    chains++;
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
void mpg_prepare(void)
{
    physical = (io_stream_t){.type = StreamType_Serial,
                             .instance = 1,
                             .write_n = transmit,
                             .write_char = transmit_char,
                             .disable_rx = disable_rx,
                             .is_connected = connected,
                             .get_tx_buffer_count = count_tx,
                             .reset_write_buffer = reset_tx,
                             .set_baud_rate = set_baud};
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.stream.write = print;
    hal.get_elapsed_ticks = ticks;
    grbl.on_report_options = options;
    grbl.on_execute_realtime = realtime;
    grbl.on_execute_delay = realtime;
    grbl.on_reset = reset;
}
void mpg_start(void)
{
    mpg_prepare();
    mpg_init();
    CHECK(registered_settings && commands);
    registered_settings->load();
}
void mpg_poll(void) { grbl.on_execute_realtime(STATE_IDLE); }
void mpg_bytes(const uint8_t *data, size_t size)
{
    CHECK(physical_rx);
    for (size_t i = 0; i < size; i++)
        CHECK(physical_rx(data[i]));
}
void mpg_receive(uint8_t seq, mpg_frame_type_t type, const uint8_t *data, uint8_t size)
{
    CHECK(size <= MPG_TRANSPORT_MAX_PAYLOAD);
    uint8_t frame[MPG_TRANSPORT_MAX_FRAME];
    size_t count = mpg_frame_build(frame, seq, type, data, size);
    mpg_bytes(frame, count);
}
void mpg_up(void)
{
    mpg_receive(0, MpgFrame_Dat, NULL, 0);
    mpg_poll();
    CHECK(packets == 1 && sent[0].data[2] == MpgFrame_Ack);
    packets = 0;
}
status_code_t mpg_command(const char *argument)
{
    CHECK(commands && commands->n_commands == 1 &&
          strcmp(commands->commands[0].command, "MPG") == 0);
    char text[64];
    char *args = NULL;
    if (argument)
    {
        CHECK(strlen(argument) < sizeof(text));
        strcpy(text, argument);
        args = text;
    }
    output[0] = 0;
    return commands->commands[0].execute(STATE_IDLE, args);
}
void mpg_ack(unsigned packet)
{
    CHECK(packet < packets && sent[packet].data[2] == MpgFrame_Dat);
    uint8_t type = MpgFrame_Dat;
    mpg_receive(sent[packet].data[1], MpgFrame_Ack, &type, 1);
    mpg_poll();
}
