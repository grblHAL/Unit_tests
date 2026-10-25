#include "at_host.h"
#include "eeprom_host.h"
#include "grbl/state_machine.h"
#include <stdio.h>
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
setting_details_t *at_settings;
bool at_uart_available = true, at_storage_available = true, at_existing_server;
bool at_prompt = true;
const char *at_fail_command;
unsigned at_fail_remaining, at_warnings, at_welcomes, at_reports, at_claims;
char at_commands[4096], at_output[4096], at_tx[512];
size_t at_tx_length;
unsigned at_control_writes;
uint8_t at_control_ports[8];
bool at_control_levels[8];
static xbar_t control_pins[2];
enqueue_realtime_command_ptr at_uart_handler;
static const char *reply = "";
static uint32_t ticks;
static io_stream_t uart, base;
static io_stream_properties_t uart_properties;
static enqueue_realtime_command_ptr base_handler;
static struct
{
    foreground_task_ptr fn;
    void *data;
    uint32_t delay;
} tasks[256];
static unsigned head, tail;
#if ETHERNET_ENABLE
static sys_commands_t *net_commands;
#endif
static void output(const char *text)
{
    CHECK(strlen(at_output) + strlen(text) < sizeof(at_output));
    strcat(at_output, text);
}
static int32_t base_read(void) { return SERIAL_NO_DATA; }
static int32_t uart_read(void) { return *reply ? (uint8_t)*reply++ : SERIAL_NO_DATA; }
static uint16_t tx_count(void) { return 0; }
static void reset_rx(void) { reply = ""; }
static bool disable_rx(bool disable)
{
    (void)disable;
    return true;
}
static uint32_t elapsed(void) { return ticks++; }
static void delay_ms(uint32_t ms, delay_callback_ptr callback)
{
    CHECK(ms && ms <= 1000 && !callback);
    ticks += ms;
}
static enqueue_realtime_command_ptr set_rt(enqueue_realtime_command_ptr fn)
{
    enqueue_realtime_command_ptr previous = at_uart_handler;
    if (fn)
        at_uart_handler = fn;
    return previous;
}
static enqueue_realtime_command_ptr base_rt(enqueue_realtime_command_ptr fn)
{
    enqueue_realtime_command_ptr previous = base_handler;
    if (fn)
        base_handler = fn;
    return previous;
}
static bool put_byte(const uint8_t c)
{
    CHECK(at_tx_length < sizeof(at_tx));
    at_tx[at_tx_length++] = c;
    return true;
}
static void modem_write(const char *text)
{
    if (!strcmp(text, ASCII_EOL) || !strcmp(text, "+++"))
        return;
    CHECK(strlen(at_commands) + strlen(text) + 2 < sizeof(at_commands));
    strcat(at_commands, text);
    strcat(at_commands, "\n");
    if (at_fail_command && !strcmp(text, at_fail_command) && at_fail_remaining)
    {
        at_fail_remaining--;
        reply = "ERROR\r\n";
        return;
    }
    if (!strcmp(text, "AT+CIPSERVER?"))
        reply = at_existing_server ? "+CIPSERVER:1,23\r\nOK\r\n" : "+CIPSERVER:0\r\nOK\r\n";
    else if (!strcmp(text, "AT+CWJAP=\"Shop\",\"fixturepass\""))
        reply = "WIFI GOT IP\r\nOK\r\n";
    else if (!strcmp(text, "AT+CIPSTA?"))
        reply = "+CIPSTA:ip:\"192.168.5.20\"\r\n+CIPSTA:gateway:\"192.168.5.1\"\r\n+CIPSTA:netmask:"
                "\"255.255.255.0\"\r\nOK\r\n";
    else if (!strcmp(text, "AT+CIPAP?"))
        reply = "+CIPAP:ip:\"192.168.5.1\"\r\n+CIPAP:gateway:\"192.168.5.1\"\r\n+CIPAP:netmask:"
                "\"255.255.255.0\"\r\nOK\r\n";
    else if (!strcmp(text, "AT+CIPSTAMAC?"))
        reply = "+CIPSTAMAC:\"02:00:00:01:02:03\"\r\nOK\r\n";
    else if (!strcmp(text, "AT+CIPAPMAC?"))
        reply = "+CIPAPMAC:\"02:00:00:01:02:04\"\r\nOK\r\n";
    else if (!strcmp(text, "AT+CIPSEND"))
        reply = at_prompt ? "OK\r\n>" : "OK\r\n";
    else
    {
        const char *known[] = {"ATE0",
                               "AT+SYSMSG=4",
                               "AT+CIPSERVER=0,1",
                               "AT+CWMODE=1,0",
                               "AT+CWMODE=2",
                               "AT+CWDHCP=1,1",
                               "AT+CIPSTA=\"192.168.5.1\"",
                               "AT+CIPAP=\"192.168.5.1\"",
                               "AT+CWHOSTNAME=\"grblHAL\"",
                               "AT+CWHOSTNAME=\"grblHAL_AP\"",
                               "AT+CWSAP=\"grblHAL_AP\",\"grblHALpwd\",5,4,1,0",
                               "AT+CIPMODE=0",
                               "AT+CIPMODE=1",
                               "AT+CIPMUX=1",
                               "AT+CIPSERVERMAXCONN=1",
                               "AT+CIPSERVER=1,23",
                               "AT+CWQIF"};
        bool found = false;
        for (unsigned i = 0; i < sizeof(known) / sizeof(*known); i++)
            found |= !strcmp(text, known[i]);
        CHECK(found);
        reply = "OK\r\n";
    }
}
static const io_stream_t *claim(uint32_t baud)
{
    CHECK(baud == 115200 && !uart_properties.flags.claimed);
    at_claims++;
    if (!at_uart_available)
        return NULL;
    uart_properties.flags.claimed = On;
    return &uart;
}
static void report_options(bool newopt)
{
    (void)newopt;
    at_reports++;
}
static void welcome(stream_write_ptr write)
{
    CHECK(write);
    at_welcomes++;
}
void at_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.delay_ms = delay_ms;
    hal.get_elapsed_ticks = elapsed;
    grbl.on_report_options = report_options;
    grbl.report.init_message = welcome;
    sys.driver_started = On;
    base = (io_stream_t){.type = StreamType_Serial,
                         .instance = 0,
                         .read = base_read,
                         .write = output,
                         .set_enqueue_rt_handler = base_rt,
                         .disable_rx = disable_rx,
                         .get_tx_buffer_count = tx_count};
    CHECK(stream_connect(&base));
    uart = (io_stream_t){.type = StreamType_Serial,
                         .instance = 1,
                         .read = uart_read,
                         .write = modem_write,
                         .write_char = put_byte,
                         .reset_read_buffer = reset_rx,
                         .get_tx_buffer_count = tx_count,
                         .set_enqueue_rt_handler = set_rt,
                         .disable_rx = disable_rx};
    static io_stream_details_t streams;
    uart_properties = (io_stream_properties_t){
        .type = StreamType_Serial, .instance = 1, .flags.claimable = On, .claim = claim};
    streams = (io_stream_details_t){.n_streams = 1, .streams = &uart_properties};
    stream_register_streams(&streams);
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 1024);
    return at_storage_available ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    if (details->is_core)
        return true;
    CHECK(!at_settings);
    at_settings = details;
    return true;
}
const setting_detail_t *at_setting(setting_id_t id)
{
    CHECK(at_settings);
    for (unsigned i = 0; i < at_settings->n_settings; i++)
        if (at_settings->settings[i].id == id)
            return &at_settings->settings[i];
    CHECK(false);
    return NULL;
}
void at_setting_string(setting_id_t id, const char *text)
{
    const setting_detail_t *d = at_setting(id);
    CHECK(d->type == Setting_NonCore &&
          (d->datatype == Format_String || d->datatype == Format_Password));
    CHECK(strlen(text) <= 32);
    strcpy(d->value, text);
}
void at_load(grbl_wifi_mode_t mode)
{
    void esp_at_init(void);
    esp_at_init();
    CHECK(at_settings);
    at_settings->restore();
    *(grbl_wifi_mode_t *)at_setting(Setting_WifiMode)->value = mode;
    if (mode == WiFiMode_STA)
    {
        at_setting_string(Setting_WiFi_STA_SSID, "Shop");
        at_setting_string(Setting_WiFi_STA_Password, "fixturepass");
    }
    at_settings->save();
    at_settings->load();
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    CHECK(fn && tail < 256);
    tasks[tail].fn = fn;
    tasks[tail].data = data;
    tasks[tail++].delay = delay;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    return task_add_delayed(fn, data, 0);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_delayed(fn, data, 0);
}
unsigned at_pending(void) { return tail - head; }
void at_step(uint32_t delay)
{
    CHECK(head < tail && tasks[head].delay == delay);
    foreground_task_ptr fn = tasks[head].fn;
    void *data = tasks[head++].data;
    ticks += delay;
    fn(data);
}
void at_start(void)
{
    at_step(0);
    at_step(1500);
    at_ready();
}
void at_modem_data(const char *text)
{
    CHECK(!*reply);
    reply = text;
}
void at_connect(void)
{
    at_modem_data("0,CONNECT\r\n");
    for (unsigned i = 0; i < 11; i++)
        at_step(i == 0 ? 100 : 2);
    at_step(2);
    CHECK(hal.stream.type == StreamType_Telnet && at_uart_handler);
}
bool at_command_seen(const char *text) { return strstr(at_commands, text) != NULL; }
void report_warning(void *message)
{
    CHECK(message);
    at_warnings++;
    output(message);
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(version, "0.08"));
    output(name);
}
void report_message(const char *text, message_type_t type)
{
    (void)type;
    output(text);
}
bool protocol_enqueue_realtime_command(uint8_t c)
{
    (void)c;
    return false;
}
sys_state_t state_get(void) { return STATE_IDLE; }
void report_add_realtime(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report)
{
    (void)write;
    (void)report;
    CHECK(false);
}
void gc_filestream_changed(vfs_file_t *file)
{
    (void)file;
    CHECK(false);
}
void task_execute(bool wait)
{
    (void)wait;
    CHECK(false);
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    CHECK(id == Settings_IoPort_InvertOut && !trim);
    (void)mask;
}
void settings_write_global(void) { CHECK(false); }
report_tracking_flags_t report_get_rt_flags_all(void)
{
    CHECK(false);
    return (report_tracking_flags_t){0};
}
void report_gcode_modes(stream_write_ptr write)
{
    (void)write;
    CHECK(false);
}
void system_register_commands(sys_commands_t *commands)
{
#if ETHERNET_ENABLE
    CHECK(!net_commands && commands->n_commands == 1 &&
          !strcmp(commands->commands[0].command, "NETIF"));
    net_commands = commands;
#else
    (void)commands;
    CHECK(false);
#endif
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
static xbar_t *control_info(io_port_direction_t direction, uint8_t port)
{
    return direction == Port_Output && port < 2 ? &control_pins[port] : NULL;
}
static void control_description(io_port_direction_t direction, uint8_t port, const char *text)
{
    CHECK(direction == Port_Output && port < 2 && text);
    control_pins[port].description = text;
}
static bool control_function(xbar_t *pin, pin_function_t function)
{
    CHECK(pin->id < 2);
    control_pins[pin->id].function = function;
    return true;
}
static void control_output(uint8_t port, bool level)
{
    CHECK(port < 2 && at_control_writes < 8);
    at_control_ports[at_control_writes] = port;
    at_control_levels[at_control_writes++] = level;
}
void at_controls(bool both)
{
    for (unsigned i = 0; i < 2; i++)
        control_pins[i] = (xbar_t){.id = i,
                                   .pin = i,
                                   .function = Output_Aux0 + i,
                                   .group = PinGroup_AuxOutput,
                                   .cap.output = On,
                                   .cap.claimable = On,
                                   .mode.output = On,
                                   .set_function = control_function};
    static io_ports_data_t data;
    static io_digital_t bank;
    data.out.n_ports = 2;
    bank = (io_digital_t){.ports = &data,
                          .get_pin_info = control_info,
                          .digital_out = control_output,
                          .set_pin_description = control_description};
    CHECK(ioports_add_digital(&bank));
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Output, 0);
    CHECK(pin && ioport_set_function(pin, Output_CoProc_Reset, (driver_caps_t){0}));
    if (both)
    {
        pin = ioport_get_info(Port_Digital, Port_Output, 1);
        CHECK(pin && ioport_set_function(pin, Output_CoProc_Boot0, (driver_caps_t){0}));
    }
}
void at_ready(void)
{
    // Deliver queued immediate callbacks; timer priority/timing is outside this model.
    for (unsigned i = head; i < tail;)
    {
        if (tasks[i].delay)
        {
            i++;
            continue;
        }
        foreground_task_ptr fn = tasks[i].fn;
        void *data = tasks[i].data;
        memmove(&tasks[i], &tasks[i + 1], (tail - i - 1) * sizeof(*tasks));
        tail--;
        fn(data);
    }
}
#if ETHERNET_ENABLE
typedef struct
{
    network_info_t *info;
    network_flags_t flags;
    unsigned count;
} network_capture_t;
static bool capture_network(network_info_t *info, network_flags_t flags, void *context)
{
    network_capture_t *capture = context;
    CHECK(info && !strcmp(info->interface, "at0") && !capture->count++);
    *capture->info = *info;
    capture->flags = flags;
    return false;
}
network_flags_t at_network_info(network_info_t *info)
{
    network_capture_t capture = {.info = info};
    CHECK(!networking_enumerate_interfaces(capture_network, &capture) && capture.count == 1);
    return capture.flags;
}
status_code_t at_netif(void)
{
    CHECK(net_commands);
    return net_commands->commands[0].execute(STATE_IDLE, NULL);
}
#endif
