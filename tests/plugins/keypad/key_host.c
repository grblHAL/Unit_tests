#include "key_host.h"
system_t sys;
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
setting_details_t *key_settings;
sys_state_t key_state = STATE_IDLE;
bool key_bus_ok = true, key_probe_ok = true, key_irq_ok = true, key_storage_ok = true,
     key_uart_ok = true, key_gcode_ok = true, key_preview;
unsigned key_gcodes, key_systems, key_reports, key_modes, key_data_changes, key_realtime_count,
    key_previous_reports;
char key_gcode[64], key_system[16], key_version[64];
uint8_t key_realtime[64], key_memory[1024];
jogdata_t key_data;
static foreground_task_ptr tasks[32];
static void *task_data[32];
static unsigned head, tail;
irq_callback_ptr strobe;
stream_write_char_ptr uart_input;
uint8_t pending_key;
static bool nv_write(uint32_t dest, uint8_t *data, uint32_t size, bool crc)
{
    CHECK(crc && dest + size + 2 <= sizeof(key_memory));
    memcpy(key_memory + dest, data, size);
    uint16_t sum = modbus_crc16x(data, size);
    key_memory[dest + size] = sum & 255;
    key_memory[dest + size + 1] = sum >> 8;
    return true;
}
static bool nv_read(uint8_t *data, uint32_t source, uint32_t size, bool crc)
{
    CHECK(crc && source + size + 2 <= sizeof(key_memory));
    memcpy(data, key_memory + source, size);
    return modbus_crc16x(data, size) ==
           (uint16_t)(key_memory[source + size] | key_memory[source + size + 1] << 8);
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size == sizeof(jog_settings_t));
    return key_storage_ok ? 128 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!key_settings);
    key_settings = details;
    return true;
}
i2c_cap_t i2c_start(void) { return (i2c_cap_t){.started = key_bus_ok}; }
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == KEYPAD_I2CADDR);
    return key_probe_ok;
}
bool i2c_get_keycode(i2c_address_t address, keycode_callback_ptr callback)
{
    CHECK(address == KEYPAD_I2CADDR && callback);
    callback((char)pending_key);
    return true;
}
static bool claim_irq(irq_type_t type, uint_fast8_t id, irq_callback_ptr fn)
{
    CHECK(type == IRQ_I2C_Strobe && id == 0);
    if (key_irq_ok)
        strobe = fn;
    return key_irq_ok;
}
const io_stream_t *stream_open_instance(uint8_t instance, uint32_t baud,
                                        stream_write_char_ptr input, const char *description)
{
    static io_stream_t stream;
    CHECK(instance == KEYPAD_STREAM && baud == 115200 && !strcmp(description, "Keypad"));
    if (key_uart_ok)
        uart_input = input;
    return key_uart_ok ? &stream : NULL;
}
static bool realtime(uint8_t c)
{
    CHECK(key_realtime_count < 64);
    key_realtime[key_realtime_count++] = c;
    return true;
}
static bool gcode(char *text)
{
    CHECK(strlen(text) < sizeof(key_gcode));
    strcpy(key_gcode, text);
    key_gcodes++;
    return key_gcode_ok;
}
status_code_t system_execute_line(char *text, stream_write_ptr write)
{
    CHECK(write == hal.stream.write && strlen(text) < sizeof(key_system));
    strcpy(key_system, text);
    key_systems++;
    return Status_OK;
}
static void output(const char *text) { (void)text; }
static void delay(uint32_t ms, delay_callback_ptr callback) { CHECK(ms == 510 && !callback); }
static void previous_report(bool newopt)
{
    (void)newopt;
    key_previous_reports++;
}
static bool preview(char code, uint_fast16_t state)
{
    (void)code;
    CHECK(state == (uint_fast16_t)key_state);
    return key_preview;
}
static void mode_changed(jogmode_t mode)
{
    CHECK(mode <= JogMode_Step);
    key_modes++;
}
static void data_changed(jogdata_t *data)
{
    key_data = *data;
    key_data_changes++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "Keypad") && strlen(version) < sizeof(key_version));
    strcpy(key_version, version);
}
void report_add_realtime(report_tracking_t report)
{
    CHECK(report == Report_CycleStart);
    key_reports++;
}
bool stream_mpg_enable(bool on)
{
    hal.stream.state.is_mpg = on;
    return true;
}
char *gc_coord_system_to_str(coord_system_id_t id)
{
    static char text[8];
    CHECK(id < N_WorkCoordinateSystems);
    snprintf(text, sizeof(text), "G%d", 54 + (int)id);
    return text;
}
sys_state_t state_get(void) { return key_state; }
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(head < 32);
    tasks[head] = fn;
    task_data[head++] = data;
    return true;
}
void key_run(void)
{
    while (tail < head)
    {
        unsigned i = tail++;
        tasks[i](task_data[i]);
    }
    head = tail = 0;
}
void key_enqueue(uint8_t code)
{
#if KEYPAD_ENABLE == 1
    pending_key = code;
    CHECK(strobe && strobe(0, true));
#else
    CHECK(uart_input && uart_input(code));
#endif
}
void key_release(void)
{
#if KEYPAD_ENABLE == 1
    CHECK(strobe && strobe(0, false));
#else
    CHECK(uart_input && uart_input(CMD_JOG_CANCEL));
#endif
}
void key_press(uint8_t code)
{
    key_enqueue(code);
    key_run();
}
void key_prepare(void)
{
    memset(key_memory, 255, sizeof(key_memory));
    hal.nvs.memcpy_to_nvs = nv_write;
    hal.nvs.memcpy_from_nvs = nv_read;
    hal.delay_ms = delay;
    hal.irq_claim = claim_irq;
    hal.stream.write = output;
    grbl.enqueue_realtime_command = realtime;
    grbl.enqueue_gcode = gcode;
    grbl.on_report_options = previous_report;
    keypad.on_keypress_preview = preview;
    keypad.on_jogmode_changed = mode_changed;
    keypad.on_jogdata_changed = data_changed;
}
void key_load(void)
{
    CHECK(keypad_init() && key_settings);
    key_settings->load();
}
void key_setting(setting_id_t id, float value)
{
    for (unsigned i = 0; i < key_settings->n_settings; i++)
    {
        const setting_detail_t *d = &key_settings->settings[i];
        if (d->id == id)
        {
            CHECK(d->datatype == Format_Decimal);
            *(float *)d->value = value;
            return;
        }
    }
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
