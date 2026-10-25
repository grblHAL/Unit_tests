#include "macro_host.h"
grbl_t grbl;
keypad_t keypad;
parser_state_t gc_state;
setting_details_t *macro_settings;
bool macro_storage = true;
sys_state_t macro_state = STATE_IDLE;
unsigned macro_resets, macro_statuses, macro_syncs, macro_warnings;
char macro_output[256];
int32_t macro_serial_read(void) { return SERIAL_NO_DATA; }
static void reset(void) { macro_resets++; }
static status_code_t status(status_code_t code)
{
    macro_statuses++;
    return code;
}
static void options(bool newopt) { (void)newopt; }
static void output(const char *text)
{
    CHECK(text && strlen(macro_output) + strlen(text) < sizeof(macro_output));
    strcat(macro_output, text);
}
void macro_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.stream =
        (io_stream_t){.type = StreamType_Serial, .read = macro_serial_read, .write = output};
    hal.driver_reset = reset;
    grbl.on_report_options = options;
    grbl.report.status_message = status;
    macros_init();
    if (macro_settings)
        macro_settings->load();
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size > 0 && size < 1024);
    return macro_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details && !macro_settings);
    macro_settings = details;
    return true;
}
void macro_set_text(unsigned index, const char *text)
{
    CHECK(macro_settings && index < 4 && strlen(text) <= 127);
    const setting_detail_t *detail = &macro_settings->settings[0];
    CHECK(detail->id == Setting_MacroBase && detail->datatype == Format_String);
    char value[128];
    strcpy(value, text);
    CHECK(((setting_set_string_ptr)detail->value)(detail->id + index, value) == Status_OK);
}
void macro_run_mcode(unsigned index)
{
    CHECK(index < 4);
    parser_block_t block = {.user_mcode = Macro_Execute0 + index};
    CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    grbl.user_mcode.execute(macro_state, &block);
}
void macro_read_text(char *buffer, size_t size)
{
    size_t count = 0;
    int32_t c;
    while ((c = hal.stream.read()) != SERIAL_NO_DATA)
    {
        CHECK(count + 1 < size);
        buffer[count++] = (char)c;
    }
    buffer[count] = 0;
}
sys_state_t state_get(void) { return macro_state; }
void protocol_buffer_synchronize(void) { macro_syncs++; }
void report_message(const char *text, message_type_t type)
{
    (void)type;
    output(text);
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "Macros") && !strcmp(version, "0.23"));
}
void report_warning(void *message)
{
    CHECK(message);
    macro_warnings++;
}
bool task_run_on_startup(foreground_task_ptr task, void *data)
{
    CHECK(task == report_warning);
    task(data);
    return true;
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
bool stream_await_tx_clear(const io_stream_t *stream)
{
    (void)stream;
    CHECK(false);
    return false;
}
