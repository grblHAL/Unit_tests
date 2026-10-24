#include "bt_host.h"

#include "grbl/state_machine.h"
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
setting_details_t *bt_settings;
bool bt_uart_ok = true, bt_storage_ok = true, bt_pin_high, bt_irq_ok = true;
unsigned bt_warnings, bt_commands, bt_fail_command, bt_timeout_command, bt_claims, bt_irqs,
    bt_welcomes, bt_prior_reports, bt_plugins, bt_base_disables;
uint32_t bt_baud[16];
unsigned bt_bauds;
char bt_output[2048], bt_command_log[256];
enqueue_realtime_command_ptr bt_base_handler, bt_uart_handler;
static xbar_t pins[2];
static ioport_interrupt_callback_ptr irq;
static uint8_t irq_port;
static uint32_t ticks;
static const char *reply = "";
static struct
{
    foreground_task_ptr fn;
    void *data;
} tasks[16];
static unsigned head, tail;
static io_stream_t base, uart;
static void output(const char *text)
{
    CHECK(strlen(bt_output) + strlen(text) < sizeof(bt_output));
    strcat(bt_output, text);
}
static int32_t base_read(void) { return SERIAL_NO_DATA; }
static int32_t uart_read(void) { return *reply ? (uint8_t)*reply++ : SERIAL_NO_DATA; }
static enqueue_realtime_command_ptr base_rt(enqueue_realtime_command_ptr fn)
{
    enqueue_realtime_command_ptr old = bt_base_handler;
    bt_base_handler = fn;
    return old;
}
static enqueue_realtime_command_ptr uart_rt(enqueue_realtime_command_ptr fn)
{
    enqueue_realtime_command_ptr old = bt_uart_handler;
    bt_uart_handler = fn;
    return old;
}
static bool baud(uint32_t value)
{
    CHECK(value == 115200 || value == 38400);
    CHECK(bt_bauds < 16);
    bt_baud[bt_bauds++] = value;
    return true;
}
static void uart_write(const char *text)
{
    if (strncmp(text, "AT", 2))
    {
        output(text);
        return;
    }
    CHECK(strlen(bt_command_log) + strlen(text) < sizeof(bt_command_log));
    strcat(bt_command_log, text);
    bt_commands++;
    reply = bt_timeout_command == bt_commands ? ""
            : bt_fail_command == bt_commands  ? "ERROR\r\n"
                                              : "\nOK\r\n";
}
static void reset_rx(void) { reply = ""; }
static bool base_disable(bool disable)
{
    if (disable)
        bt_base_disables++;
    return true;
}
static bool uart_disable(bool disable)
{
    (void)disable;
    return true;
}
static uint32_t elapsed(void) { return ticks++; }
static uint16_t tx_count(void) { return 0; }
static void welcome(stream_write_ptr write)
{
    CHECK(write);
    bt_welcomes++;
    write("Welcome\r\n");
}
static void report_options(bool newopt)
{
    (void)newopt;
    bt_prior_reports++;
}
static const io_stream_t *claim_uart(uint32_t rate)
{
    CHECK(rate == 115200);
    bt_claims++;
    return bt_uart_ok ? &uart : NULL;
}
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Input && port < 2 ? &pins[port] : NULL;
}
static void description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Input && port < 2);
    pins[port].description = text;
}
static float pin_value(xbar_t *p)
{
    CHECK(p == &pins[0] || p == &pins[1]);
    return bt_pin_high;
}
static int32_t wait_input(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < 2 && mode == WaitMode_Immediate && timeout == 0);
    return bt_pin_high;
}
static bool register_irq(uint8_t physical, uint8_t user, pin_irq_mode_t mode,
                         ioport_interrupt_callback_ptr handler)
{
    CHECK(physical < 2 && mode == IRQ_Mode_Change && handler);
    bt_irqs++;
    if (!bt_irq_ok)
        return false;
    irq = handler;
    irq_port = user;
    return true;
}
void bt_prepare(unsigned inputs, bool irq_capable)
{
    CHECK(inputs <= 2);
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.get_elapsed_ticks = elapsed;
    grbl.on_report_options = report_options;
    grbl.report.init_message = welcome;
    sys.driver_started = On;
    base = (io_stream_t){.type = StreamType_Serial,
                         .instance = 0,
                         .read = base_read,
                         .write = output,
                         .reset_read_buffer = reset_rx,
                         .set_enqueue_rt_handler = base_rt,
                         .disable_rx = base_disable,
                         .get_tx_buffer_count = tx_count};
    uart = (io_stream_t){.type = StreamType_Serial,
                         .instance = 1,
                         .read = uart_read,
                         .write = uart_write,
                         .reset_read_buffer = reset_rx,
                         .set_enqueue_rt_handler = uart_rt,
                         .set_baud_rate = baud,
                         .disable_rx = uart_disable,
                         .get_tx_buffer_count = tx_count};
    CHECK(stream_connect(&base));
    static io_stream_properties_t prop;
    static io_stream_details_t ports;
    prop = (io_stream_properties_t){.type = StreamType_Serial,
                                    .instance = 1,
                                    .flags.claimable = On,
                                    .flags.can_set_baud = On,
                                    .claim = claim_uart};
    ports = (io_stream_details_t){.n_streams = 1, .streams = &prop};
    stream_register_streams(&ports);
    if (inputs)
    {
        for (unsigned i = 0; i < inputs; i++)
        {
            pins[i] = (xbar_t){
                .id = i, .function = Input_Aux0 + i, .cap.input = On, .get_value = pin_value};
            pins[i].cap.irq_mode = irq_capable ? IRQ_Mode_Change : IRQ_Mode_None;
        }
        static io_ports_data_t data;
        static io_digital_t io;
        data.in.n_ports = inputs;
        io = (io_digital_t){.ports = &data,
                            .get_pin_info = pin_info,
                            .set_pin_description = description,
                            .wait_on_input = wait_input,
                            .register_interrupt_handler = register_irq};
        CHECK(ioports_add_digital(&io));
    }
}
nvs_address_t nvs_alloc(size_t size)
{
    static nvs_address_t next = 2048;
    CHECK(size && size < 512);
    if (!bt_storage_ok)
        return 0;
    nvs_address_t value = next;
    next += (size + NVS_CRC_BYTES + 3) & ~3U;
    CHECK(next < 8192);
    return value;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_BlueToothInitOK)
        {
            CHECK(!bt_settings);
            bt_settings = details;
        }
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    bt_warnings++;
    output(message);
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "Bluetooth HC-05") && version && *version);
    bt_plugins++;
}
void report_message(const char *text, message_type_t type)
{
    (void)type;
    output(text);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(fn && tail < 16);
    tasks[tail].fn = fn;
    tasks[tail++].data = data;
    return true;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_immediate(fn, data);
}
void bt_run(void)
{
    while (head < tail)
    {
        foreground_task_ptr fn = tasks[head].fn;
        void *data = tasks[head++].data;
        fn(data);
    }
}
void bt_edge(bool on)
{
    CHECK(irq);
    bt_pin_high = on;
    irq(irq_port, on);
    bt_run();
}
void bt_load(void)
{
    bluetooth_init();
    CHECK(bt_settings);
    bt_settings->restore();
    CHECK(bt_port(0) == Status_OK);
    bt_settings->save();
    bt_settings->load();
    bt_run();
}
const setting_detail_t *bt_setting(setting_id_t id)
{
    CHECK(bt_settings);
    for (unsigned i = 0; i < bt_settings->n_settings; i++)
        if (bt_settings->settings[i].id == id)
            return &bt_settings->settings[i];
    CHECK(false);
    return NULL;
}
uint32_t bt_enabled(void)
{
    const setting_detail_t *d = bt_setting(Setting_BlueToothInitOK);
    return ((setting_get_int_ptr)d->get_value)(d->id) & 1U;
}
void bt_enable(bool on)
{
    const setting_detail_t *d = bt_setting(Setting_BlueToothInitOK);
    CHECK(((setting_set_int_ptr)d->value)(d->id, on) == Status_OK);
}
void bt_name(const char *name)
{
    const setting_detail_t *d = bt_setting(Setting_BlueToothDeviceName);
    CHECK(d->datatype == Format_String && strlen(name) <= 32);
    strcpy(d->value, name);
}
void bt_init_configured(void)
{
    bluetooth_init();
    CHECK(bt_settings);
    bt_settings->restore();
    CHECK(bt_port(0) == Status_OK);
    bt_enable(true);
    bt_settings->save();
    bt_settings->load();
    bt_run();
}
// shortcut: unused CORE stream paths fail here; extend when adding full protocol/MPG integration.
bool protocol_enqueue_realtime_command(uint8_t c)
{
    (void)c;
    CHECK(false);
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
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    (void)fn;
    (void)data;
    (void)delay;
    CHECK(false);
    return false;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
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

void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id;
    (void)mask;
    (void)trim;
    CHECK(false);
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
    (void)commands;
    CHECK(false);
}

status_code_t bt_port(float port)
{
    const setting_detail_t *d = bt_setting(Setting_BlueToothStateInput);
    return ((setting_set_float_ptr)d->value)(d->id, port);
}
