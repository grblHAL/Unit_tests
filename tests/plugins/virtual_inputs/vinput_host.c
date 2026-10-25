#include "vinput_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
char output[512];
unsigned warnings, resets, unknown_calls, option_calls, registrations;
bool unknown_result = false;
sys_commands_t *registered_commands;
static bool pins[3];
static ioport_interrupt_callback_ptr irqs[3];
static pin_irq_mode_t modes[3];
static bool read_pin(void *pin)
{
#if !VI_SEPARATE
    if (pin == &pins[0])
        return pins[0] || pins[1];
#endif
    return *(bool *)pin;
}
static void set_bits(volatile uint_fast16_t *value, uint_fast16_t bits) { *value |= bits; }
static uint_fast16_t clear_bits(volatile uint_fast16_t *value, uint_fast16_t bits)
{
    uint_fast16_t old = *value;
    *value &= ~bits;
    return old;
}
static void write_text(const char *text)
{
    CHECK(strlen(output) + strlen(text) < sizeof(output));
    strcat(output, text);
}
static void previous_reset(void) { resets++; }
static bool previous_unknown(char c)
{
    CHECK((uint8_t)c == 0xB8);
    unknown_calls++;
    return unknown_result;
}
static void previous_options(bool newopt)
{
    (void)newopt;
    option_calls++;
}
bool ioport_enable_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr handler)
{
    CHECK(port < 3);
    irqs[port] = handler;
    modes[port] = mode;
    return true;
}
void report_add_realtime(report_tracking_t report) { CHECK(report == Report_ProbeProtect); }
void report_warning(void *data) { CHECK(data); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    warnings++;
    return true;
}
void system_register_commands(sys_commands_t *commands)
{
    CHECK(!registered_commands);
    registered_commands = commands;
    registrations++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Virtual inputs") == 0 && strcmp(version, "0.05") == 0);
    option_calls++;
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
void vi_prepare(bool chain)
{
    hal.set_bits_atomic = set_bits;
    hal.clear_bits_atomic = clear_bits;
    hal.stream.write = write_text;
    grbl.on_report_options = previous_options;
    if (chain)
    {
        grbl.on_reset = previous_reset;
        grbl.on_unknown_realtime_cmd = previous_unknown;
    }
}
void vi_start(bool chain)
{
    vi_prepare(chain);
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_RisingFalling, &pins[0], read_pin));
#if VI_SEPARATE
    CHECK(probe_add(Probe_Toolsetter, 1, IRQ_Mode_RisingFalling, &pins[1], read_pin));
#endif
    CHECK(probe_add(Probe_2, 2, IRQ_Mode_RisingFalling, &pins[2], read_pin));
    hal.probe.configure(false, false);
    virtual_inputs_init();
    CHECK(registered_commands);
}
status_code_t vi_command(const char *args)
{
    CHECK(registered_commands && registered_commands->n_commands == 1);
    CHECK(strcmp(registered_commands->commands[0].command, "VI") == 0);
    char copy[64];
    char *argument = NULL;
    if (args)
    {
        CHECK(strlen(args) < sizeof(copy));
        strcpy(copy, args);
        argument = copy;
    }
    output[0] = 0;
    return registered_commands->commands[0].execute(STATE_IDLE, argument);
}
void vi_configure(bool away, bool probing) { hal.probe.configure(away, probing); }
void vi_select(probe_id_t id) { CHECK(hal.probe.select && hal.probe.select(id)); }
void vi_physical(probe_id_t id, bool contact)
{
    CHECK(id <= Probe_2);
    pins[id] = contact;
    if (irqs[id] &&
        ((contact && modes[id] == IRQ_Mode_Rising) || (!contact && modes[id] == IRQ_Mode_Falling)))
        irqs[id]((uint8_t)id, contact);
}
