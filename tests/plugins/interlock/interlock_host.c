#include "interlock_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
setting_details_t *registered_settings;
spindle_ptrs_t spindle;
unsigned input_count = 4, output_count = 4, hardware_spindles, hardware_outputs;
unsigned warnings, resets, chains, saves, startup_warnings;
bool alloc_ok = true, select_ok = true, output_value;
float levels[2][4];
char warning[256];
static uint8_t nvs[64];
static size_t stored;
static xbar_t pins[2][4];
static float read_pin(xbar_t *pin)
{
    for (unsigned d = 0; d < 2; d++)
        for (unsigned p = 0; p < 4; p++)
            if (pin == &pins[d][p])
                return levels[d][p];
    CHECK(false);
    return -1;
}
xbar_t *ioport_get_info(io_port_type_t type, io_port_direction_t dir, uint8_t port)
{
    CHECK(type == Port_Digital);
    if (port >= (dir == Port_Input ? input_count : output_count))
        return NULL;
    pins[dir][port].get_value = read_pin;
    return &pins[dir][port];
}
io_port_cfg_t *ioports_cfg(io_port_cfg_t *p, io_port_type_t type, io_port_direction_t dir)
{
    CHECK(type == Port_Digital);
    unsigned n = dir == Port_Input ? input_count : output_count;
    io_port_cfg_t cfg = {.n_ports = n, .port_max = n ? n - 1 : 0};
    memcpy(p, &cfg, sizeof(cfg));
    // The real API provides persistent decimal limits in this inline field.
    char max[4] = {0};
    if (n)
        snprintf(max, sizeof(max), "%u", n - 1);
    memcpy((char *)p + offsetof(io_port_cfg_t, port_maxs), max, sizeof(max));
    return p;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size <= sizeof(nvs));
    return alloc_ok ? 2048 : 0;
}
static nvs_transfer_result_t nvs_read(uint8_t *dst, uint32_t addr, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    if (!stored)
        return (nvs_transfer_result_t)0;
    CHECK(size == stored);
    memcpy(dst, nvs, size);
    return NVS_TransferResult_OK;
}
static nvs_transfer_result_t nvs_write(uint32_t addr, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return NVS_TransferResult_OK;
}
bool settings_register(setting_details_t *s)
{
    CHECK(!registered_settings);
    registered_settings = s;
    return true;
}
void report_warning(void *data) { CHECK(data); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    startup_warnings++;
    return true;
}
void report_message(const char *text, message_type_t type)
{
    CHECK(type == Message_Warning && strlen(text) < sizeof(warning));
    strcpy(warning, text);
    warnings++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Interlock") == 0 && strcmp(version, "0.6") == 0);
    chains++;
}
void mc_reset(void) { resets++; }
static uint_fast16_t set_atomic(volatile uint_fast16_t *value, uint_fast16_t next)
{
    uint_fast16_t old = *value;
    *value = next;
    return old;
}
static void set_spindle(spindle_ptrs_t *s, spindle_state_t state, float rpm)
{
    CHECK(s == &spindle);
    (void)state;
    (void)rpm;
    hardware_spindles++;
}
static void digital(uint8_t port, bool on)
{
    CHECK(port < output_count);
    hardware_outputs++;
    output_value = on;
}
static bool select_spindle(spindle_ptrs_t *s)
{
    CHECK(s == &spindle);
    chains++;
    return select_ok;
}
static void programmed(spindle_ptrs_t *s, spindle_state_t state, float rpm, spindle_rpm_mode_t mode)
{
    CHECK(s == &spindle);
    (void)state;
    (void)rpm;
    (void)mode;
    chains++;
}
static void realtime(sys_state_t state)
{
    (void)state;
    chains++;
}
static void options(bool newopt)
{
    (void)newopt;
    chains++;
}
void il_prepare(void)
{
    hal.nvs.memcpy_from_nvs = nvs_read;
    hal.nvs.memcpy_to_nvs = nvs_write;
    hal.set_value_atomic = set_atomic;
    hal.port.digital_out = digital;
    spindle.set_state = set_spindle;
    grbl.on_spindle_select = select_spindle;
    grbl.on_spindle_programmed = programmed;
    grbl.on_execute_realtime = realtime;
    grbl.on_report_options = options;
}
void il_start(void)
{
    il_prepare();
    spindle_interlock_init();
    CHECK(registered_settings);
    registered_settings->load();
    CHECK(grbl.on_spindle_select(&spindle));
}
static const setting_detail_t *find(unsigned id)
{
    CHECK(registered_settings);
    for (unsigned i = 0; i < registered_settings->n_settings; i++)
        if (registered_settings->settings[i].id == id)
            return &registered_settings->settings[i];
    CHECK(false);
    return NULL;
}
status_code_t il_float(unsigned id, float value)
{
    const setting_detail_t *s = find(id);
    return ((setting_set_float_ptr)s->value)((setting_id_t)id, value);
}
void il_int(unsigned id, uint_fast16_t value)
{
    const setting_detail_t *s = find(id);
    CHECK(((setting_set_int_ptr)s->value)((setting_id_t)id, value) == Status_OK);
}
float il_read_float(unsigned id)
{
    const setting_detail_t *s = find(id);
    CHECK(s->get_value);
    return ((setting_get_float_ptr)s->get_value)((setting_id_t)id);
}
uint32_t il_read_int(unsigned id)
{
    const setting_detail_t *s = find(id);
    CHECK(s->get_value);
    return ((setting_get_int_ptr)s->get_value)((setting_id_t)id);
}
void il_command(bool on)
{
    spindle_state_t state = {0};
    state.on = on;
    spindle.set_state(&spindle, state, on ? 1000 : 0);
}
