#include "macro_host.h"
grbl_t grbl;
system_t sys;
settings_t settings;
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
#if MACROS_ENABLE & 1
unsigned macro_inputs = 2, macro_realtime_count;
uint8_t macro_realtime[16];
bool macro_irq_ok = true;
static xbar_t macro_pins[2];
static ioport_interrupt_callback_ptr pin_handlers[2];
static uint8_t pin_users[2];
static foreground_task_ptr tasks[8];
static void *task_data[8];
static unsigned task_count;
static xbar_t *pin_info(io_port_direction_t dir, uint8_t physical)
{
    return dir == Port_Input && physical < macro_inputs ? &macro_pins[physical] : NULL;
}
static void pin_description(io_port_direction_t dir, uint8_t physical, const char *text)
{
    CHECK(dir == Port_Input && physical < macro_inputs);
    macro_pins[physical].description = text;
}
static int32_t pin_wait(uint8_t physical, wait_mode_t mode, float timeout)
{
    CHECK(physical < macro_inputs && mode == WaitMode_Immediate && timeout == 0);
    return 0;
}
static bool register_irq(uint8_t physical, uint8_t user, pin_irq_mode_t mode,
                         ioport_interrupt_callback_ptr handler)
{
    CHECK(physical < macro_inputs && user < N_AUX_DIN_MAX && mode == IRQ_Mode_Falling && handler);
    if (macro_irq_ok)
    {
        pin_handlers[physical] = handler;
        pin_users[physical] = user;
    }
    return macro_irq_ok;
}
static bool realtime(uint8_t code)
{
    CHECK(macro_realtime_count < 16);
    macro_realtime[macro_realtime_count++] = code;
    return true;
}
bool task_add_immediate(foreground_task_ptr task, void *data)
{
    CHECK(task && task_count < 8);
    tasks[task_count] = task;
    task_data[task_count++] = data;
    return true;
}
void macro_run_tasks(void)
{
    unsigned count = task_count;
    task_count = 0;
    for (unsigned i = 0; i < count; i++)
        tasks[i](task_data[i]);
}
void macro_pin(unsigned physical, bool high)
{
    CHECK(physical < macro_inputs && pin_handlers[physical]);
    pin_handlers[physical](pin_users[physical], high);
}
void macro_action(unsigned index, unsigned action)
{
    CHECK(macro_settings && index < 2 && action < 11);
    for (unsigned i = 0; i < macro_settings->n_settings; i++)
    {
        const setting_detail_t *detail = &macro_settings->settings[i];
        if (detail->id == Setting_ButtonActionBase)
        {
            CHECK(detail->datatype == Format_RadioButtons);
            CHECK(((setting_set_int_ptr)detail->value)(detail->id + index, action) == Status_OK);
            return;
        }
    }
    CHECK(false);
}
void settings_write_global(void) { CHECK(false); }
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id;
    (void)mask;
    (void)trim;
    CHECK(false);
}
#endif
void macro_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.stream =
        (io_stream_t){.type = StreamType_Serial, .read = macro_serial_read, .write = output};
    hal.driver_reset = reset;
    grbl.on_report_options = options;
    grbl.report.status_message = status;
#if MACROS_ENABLE & 1
    CHECK(macro_inputs <= 2);
    if (macro_inputs)
    {
        static io_ports_data_t ports;
        static io_digital_t digital;
        for (unsigned i = 0; i < macro_inputs; i++)
        {
            macro_pins[i] = (xbar_t){.id = i, .function = Input_Aux0 + i, .cap.input = On};
            macro_pins[i].cap.irq_mode = IRQ_Mode_Falling;
        }
        ports.in.n_ports = macro_inputs;
        digital = (io_digital_t){.ports = &ports,
                                 .get_pin_info = pin_info,
                                 .set_pin_description = pin_description,
                                 .wait_on_input = pin_wait,
                                 .register_interrupt_handler = register_irq};
        CHECK(ioports_add_digital(&digital));
    }
    grbl.enqueue_realtime_command = realtime;
#endif
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
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_MacroBase)
        {
            CHECK(!macro_settings);
            macro_settings = details;
        }
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
