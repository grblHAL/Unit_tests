#include "therm_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
setting_details_t *registered_settings;
sys_commands_t *registered_commands;
unsigned available_ports = 2, warnings, saves, claims, reads, stops, reports, options;
bool alloc_ok = true, claim_ok = true;
int32_t adc = 3102;
char output[512];
static uint8_t nvs[64];
static size_t stored;
static void write_text(const char *text)
{
    CHECK(strlen(output) + strlen(text) < sizeof(output));
    strcat(output, text);
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
    registered_settings = details;
    return true;
}
void system_register_commands(sys_commands_t *commands)
{
    CHECK(!registered_commands);
    registered_commands = commands;
}
static xbar_t *claim(io_port_cfg_t *p, uint8_t *port, const char *description, pin_cap_t caps)
{
    static xbar_t pin;
    (void)caps;
    CHECK(p->n_ports == 2 && *port < 2 && description);
    claims++;
    if (!claim_ok)
        return NULL;
    *port = 0;
    return &pin;
}
static status_code_t set_value(io_port_cfg_t *p, uint8_t *port, pin_cap_t caps, float value)
{
    (void)p;
    (void)caps;
    if (value < -1 || value >= 2)
        return Status_AuxiliaryPortUnavailable;
    *port = value < 0 ? IOPORT_UNASSIGNED : (uint8_t)value;
    return Status_OK;
}
static float get_value(io_port_cfg_t *p, uint8_t port)
{
    (void)p;
    return port == IOPORT_UNASSIGNED ? -1 : port;
}
io_port_cfg_t *ioports_cfg(io_port_cfg_t *p, io_port_type_t type, io_port_direction_t dir)
{
    CHECK(type == Port_Analog && dir == Port_Input);
    io_port_cfg_t cfg = {.n_ports = available_ports,
                         .port_max = 1,
                         .port_maxs = "1",
                         .claim = claim,
                         .set_value = set_value,
                         .get_value = get_value};
    memcpy(p, &cfg, sizeof(cfg));
    return p;
}
int32_t ioport_wait_on_input(io_port_type_t type, uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(type == Port_Analog && port == 0 && mode == WaitMode_Immediate && timeout == 0);
    reads++;
    return adc;
}
void spindle_all_off(bool reset)
{
    CHECK(reset);
    stops++;
}
static uint_fast16_t set_atomic(volatile uint_fast16_t *value, uint_fast16_t next)
{
    uint_fast16_t old = *value;
    *value = next;
    return old;
}
void report_warning(void *data) { CHECK(data); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    warnings++;
    return true;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Thermistor") == 0 && strcmp(version, "1.4") == 0);
    options++;
}
static void previous_report(stream_write_ptr write, report_tracking_flags_t flags)
{
    (void)flags;
    reports++;
    write("|previous");
}
static void previous_options(bool newopt)
{
    (void)newopt;
    options++;
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
void therm_prepare(void)
{
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.stream.write = write_text;
    hal.set_value_atomic = set_atomic;
    grbl.on_report_options = previous_options;
    grbl.on_realtime_report = previous_report;
}
void therm_float(unsigned id, float value)
{
    CHECK(registered_settings);
    for (unsigned i = 0; i < registered_settings->n_settings; i++)
    {
        const setting_detail_t *s = &registered_settings->settings[i];
        if (s->id != id)
            continue;
        if (s->type == Setting_NonCoreFn)
            CHECK(((setting_set_float_ptr)s->value)((setting_id_t)id, value) == Status_OK);
        else
        {
            CHECK(s->datatype == Format_Decimal);
            *(float *)s->value = value;
        }
        return;
    }
    CHECK(false);
}
void therm_start(bool assigned)
{
    therm_prepare();
    thermistor_init();
    CHECK(registered_settings && registered_commands);
    registered_settings->restore();
    if (assigned)
    {
        therm_float(455, 1);
        registered_settings->save();
    }
    registered_settings->load();
}
void therm_report(bool all)
{
    output[0] = 0;
    report_tracking_flags_t flags = {0};
    flags.all = all;
    grbl.on_realtime_report(write_text, flags);
}
status_code_t therm_command(const char *name, sys_state_t state, const char *args)
{
    CHECK(registered_commands);
    char text[64];
    char *argument = NULL;
    if (args)
    {
        CHECK(strlen(args) < sizeof(text));
        strcpy(text, args);
        argument = text;
    }
    output[0] = 0;
    for (unsigned i = 0; i < registered_commands->n_commands; i++)
        if (strcmp(registered_commands->commands[i].command, name) == 0)
            return registered_commands->commands[i].execute(state, argument);
    CHECK(false);
    return Status_InvalidStatement;
}
