#include "event_host.h"
#include <string.h>
#include <stdio.h>
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
setting_details_t *event_details;
bool levels[4];
uint8_t claimed_mask, missing_mask;
unsigned writes, saves, state_calls, spindle_calls, speed_calls, coolant_calls, resets, reports,
    options;
static uint8_t nvs[64];
static size_t stored;
static char descriptions[4][30] = {"P0", "P1", "P2", "P3"};
static foreground_task_ptr startup;
static void *startup_data;
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size <= sizeof(nvs));
    return 2048;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t addr, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && size <= sizeof(nvs) && checksum);
    if (!stored)
        return false;
    CHECK(size == stored);
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t addr, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && size <= sizeof(nvs) && checksum);
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return true;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!event_details);
    event_details = details;
    return true;
}
static uint8_t next_port(io_port_cfg_t *cfg, uint8_t port, const char *description, pin_cap_t caps)
{
    (void)description;
    (void)caps;
    CHECK(cfg->n_ports == 4);
    return port == IOPORT_UNASSIGNED ? 3 : (uint8_t)(port - 1);
}
static xbar_t *get_info(io_port_cfg_t *cfg, uint8_t port)
{
    static xbar_t pin;
    CHECK(cfg->n_ports == 4 && port < 4);
    if (missing_mask & (1u << port))
        return NULL;
    pin = (xbar_t){.id = port, .description = descriptions[port]};
    pin.mode.claimed = !!(claimed_mask & (1u << port));
    return &pin;
}
static status_code_t set_port(io_port_cfg_t *cfg, uint8_t *port, pin_cap_t caps, float value)
{
    (void)caps;
    CHECK(cfg->n_ports == 4 && value >= -1 && value < 4);
    *port = value < 0 ? IOPORT_UNASSIGNED : (uint8_t)value;
    return Status_OK;
}
static float get_port(io_port_cfg_t *cfg, uint8_t port)
{
    CHECK(cfg->n_ports == 4);
    return port == IOPORT_UNASSIGNED ? -1 : port;
}
io_port_cfg_t *ioports_cfg(io_port_cfg_t *cfg, io_port_type_t type, io_port_direction_t dir)
{
    CHECK(type == Port_Digital && dir == Port_Output);
    cfg->n_ports = 4;
    cfg->port_max = 3;
    cfg->get_next = next_port;
    cfg->get_info = get_info;
    cfg->set_value = set_port;
    cfg->get_value = get_port;
    return cfg;
}
bool ioport_digital_out(uint8_t port, uint32_t value)
{
    CHECK(port < 4 && value <= 1);
    levels[port] = value;
    writes++;
    return true;
}
bool ioport_set_description(io_port_type_t type, io_port_direction_t dir, uint8_t port,
                            const char *description)
{
    CHECK(type == Port_Digital && dir == Port_Output && description);
    if (port >= 4)
        return false;
    CHECK(strlen(description) < sizeof(descriptions[port]));
    strcpy(descriptions[port], description);
    return true;
}
void report_warning(void *data)
{
    (void)data;
    CHECK(false);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(!startup);
    startup = fn;
    startup_data = data;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
static void state_changed(sys_state_t state)
{
    (void)state;
    state_calls++;
}
static void spindle_programmed(spindle_ptrs_t *spindle, spindle_state_t state, float rpm,
                               spindle_rpm_mode_t mode)
{
    CHECK(spindle && rpm == 500);
    (void)state;
    (void)mode;
    spindle_calls++;
}
static void at_speed(spindle_ptrs_t *spindle, spindle_state_t state)
{
    CHECK(spindle);
    (void)state;
    speed_calls++;
}
static void coolant(coolant_state_t state)
{
    (void)state;
    coolant_calls++;
}
static void reset(void) { resets++; }
static void report_options(bool newopt)
{
    (void)newopt;
    options++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Events plugin") == 0 && strcmp(version, "0.14") == 0);
    reports++;
}
void prepare_events(void)
{
    void event_out_init(void);
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.driver_reset = reset;
    hal.coolant.set_state = coolant;
    grbl.on_state_change = state_changed;
    grbl.on_spindle_programmed = spindle_programmed;
    grbl.on_spindle_at_speed = at_speed;
    grbl.on_report_options = report_options;
    event_out_init();
    CHECK(event_details && startup);
}
void run_event_startup(void)
{
    CHECK(startup);
    foreground_task_ptr fn = startup;
    startup = NULL;
    fn(startup_data);
}
void load_events(void)
{
    prepare_events();
    event_details->load();
    run_event_startup();
    CHECK(saves == 1 && writes == 0);
}
void bind_event(unsigned slot, uint_fast16_t trigger)
{
    CHECK(slot < 4 && trigger <= 11);
    const setting_detail_t *s = event_details->settings;
    CHECK(((setting_set_int_ptr)s->value)(Setting_ActionBase + slot, trigger) == Status_OK);
}

char *ftoa(float value, uint8_t decimals)
{
    (void)value;
    (void)decimals;
    CHECK(false);
    return NULL;
}
