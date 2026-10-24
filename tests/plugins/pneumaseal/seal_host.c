#include "seal_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
setting_details_t *registered_settings;
unsigned available_ports = 2, warnings, saves, claims, outputs, chains;
bool alloc_ok = true, claim_ok = true, solenoid, live_spindle;
uint8_t output_port;
uint32_t timer_ms;
foreground_task_ptr timer;
static void *timer_data;
static sys_state_t machine_state = STATE_IDLE;
static uint8_t nvs[64];
static size_t stored;
static spindle_ptrs_t spindle;
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
static uint8_t get_next(io_port_cfg_t *p, uint8_t port, const char *description, pin_cap_t caps)
{
    (void)caps;
    CHECK(p->n_ports == 2 && description && port == IOPORT_UNASSIGNED);
    return 1;
}
static xbar_t *claim(io_port_cfg_t *p, uint8_t *port, const char *description, pin_cap_t caps)
{
    static xbar_t pin;
    (void)caps;
    CHECK(p->n_ports == 2 && description && *port < 2);
    claims++;
    if (!claim_ok)
        return NULL;
    // Model a public auxiliary number remapped after its successful claim.
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
    CHECK(type == Port_Digital && dir == Port_Output);
    io_port_cfg_t cfg = {.n_ports = available_ports,
                         .port_max = 1,
                         .port_maxs = "1",
                         .get_next = get_next,
                         .claim = claim,
                         .set_value = set_value,
                         .get_value = get_value};
    memcpy(p, &cfg, sizeof(cfg));
    return p;
}
bool ioport_digital_out(uint8_t port, uint32_t value)
{
    CHECK(port == 0 && value <= 1);
    output_port = port;
    solenoid = value;
    outputs++;
    return true;
}
static spindle_state_t get_spindle(spindle_ptrs_t *sp)
{
    CHECK(sp == &spindle);
    spindle_state_t s = {0};
    s.on = live_spindle;
    return s;
}
spindle_ptrs_t *spindle_get(spindle_num_t index)
{
    CHECK(index == 0);
    return &spindle;
}
sys_state_t state_get(void) { return machine_state; }
void report_warning(void *data) { CHECK(data); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    warnings++;
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    CHECK(!timer && delay);
    timer = fn;
    timer_data = data;
    timer_ms = delay;
    return true;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    if (timer == fn && timer_data == data)
    {
        timer = NULL;
        timer_data = NULL;
        timer_ms = 0;
    }
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "PneumaSeal") == 0 && strcmp(version, "1.5") == 0);
    chains++;
}
static void state_hook(sys_state_t state)
{
    (void)state;
    chains++;
}
static void spindle_hook(spindle_ptrs_t *sp, spindle_state_t state, float rpm,
                         spindle_rpm_mode_t mode)
{
    CHECK(sp == &spindle);
    (void)state;
    (void)rpm;
    (void)mode;
    chains++;
}
static void completed(program_flow_t flow, bool check)
{
    (void)flow;
    CHECK(!check);
    chains++;
}
static void reset(void) { chains++; }
static void options(bool newopt)
{
    (void)newopt;
    chains++;
}
void seal_prepare(void)
{
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.driver_reset = reset;
    spindle.get_state = get_spindle;
    grbl.on_state_change = state_hook;
    grbl.on_spindle_programmed = spindle_hook;
    grbl.on_program_completed = completed;
    grbl.on_report_options = options;
}
void seal_start(void)
{
    seal_prepare();
    pneumaseal_init();
    CHECK(registered_settings);
    registered_settings->load();
}
void seal_state(sys_state_t state)
{
    machine_state = state;
    grbl.on_state_change(state);
}
void seal_spindle(bool on)
{
    spindle_state_t state = {0};
    state.on = on;
    // CORE notifies programmed state before the hardware changes.
    grbl.on_spindle_programmed(&spindle, state, 1000, SpindleSpeedMode_RPM);
    live_spindle = on;
}
void seal_expire(void)
{
    CHECK(timer);
    foreground_task_ptr fn = timer;
    void *data = timer_data;
    timer = NULL;
    timer_data = NULL;
    timer_ms = 0;
    fn(data);
}
void seal_setting(unsigned id, uint_fast16_t value)
{
    CHECK(registered_settings);
    for (unsigned i = 0; i < registered_settings->n_settings; i++)
    {
        const setting_detail_t *s = &registered_settings->settings[i];
        if (s->id == id)
        {
            CHECK(((setting_set_int_ptr)s->value)((setting_id_t)id, value) == Status_OK);
            return;
        }
    }
    CHECK(false);
}
