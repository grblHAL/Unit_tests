#include "relay_host.h"
#include <string.h>
grbl_hal_t hal;
grbl_t grbl;
setting_details_t *relay_details;
bool alloc_ok = true, claims_ok = true, native_toolsetter, native_probe2, levels[2];
unsigned available = 2, saves, warnings, writes, delays, selections, reports, options;
static uint8_t nvs[2];
static bool stored;
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size == sizeof(nvs));
    return alloc_ok ? 2048 : 0;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t address, uint32_t size, bool checksum)
{
    CHECK(address == 2048 && size == sizeof(nvs) && checksum);
    if (!stored)
        return false;
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t address, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(address == 2048 && size == sizeof(nvs) && checksum);
    memcpy(nvs, src, size);
    stored = true;
    saves++;
    return true;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!relay_details);
    relay_details = details;
    return true;
}
static uint8_t next_port(io_port_cfg_t *cfg, uint8_t port, const char *description, pin_cap_t caps)
{
    (void)caps;
    CHECK(cfg->n_ports == available && description && available == 2);
    return port == IOPORT_UNASSIGNED ? 1 : (uint8_t)(port - 1);
}
static xbar_t *claim(io_port_cfg_t *cfg, uint8_t *port, const char *description, pin_cap_t caps)
{
    static xbar_t pin;
    (void)caps;
    CHECK(cfg->n_ports == available && *port < available && description);
    return claims_ok ? &pin : NULL;
}
static status_code_t set_port(io_port_cfg_t *cfg, uint8_t *port, pin_cap_t caps, float value)
{
    (void)caps;
    CHECK(cfg->n_ports == available && (value == -1 || value == 0 || value == 1));
    *port = value < 0 ? IOPORT_UNASSIGNED : (uint8_t)value;
    return Status_OK;
}
static float get_port(io_port_cfg_t *cfg, uint8_t port)
{
    CHECK(cfg->n_ports == available);
    return port == IOPORT_UNASSIGNED ? -1 : port;
}
io_port_cfg_t *ioports_cfg(io_port_cfg_t *cfg, io_port_type_t type, io_port_direction_t dir)
{
    CHECK(type == Port_Digital && dir == Port_Output);
    cfg->n_ports = available;
    cfg->get_next = next_port;
    cfg->claim = claim;
    cfg->set_value = set_port;
    cfg->get_value = get_port;
    return cfg;
}
bool ioport_digital_out(uint8_t port, uint32_t value)
{
    CHECK(port < 2 && value <= 1);
    levels[port] = value;
    writes++;
    return true;
}
static bool select_probe(probe_id_t id)
{
    selections++;
    return (id == Probe_Toolsetter && native_toolsetter) || (id == Probe_2 && native_probe2);
}
static probe_state_t probe_state(void)
{
    CHECK(false);
    return (probe_state_t){0};
}
static void delay(uint32_t ms, void (*callback)(void))
{
    CHECK(ms == 50 && callback == NULL);
    delays++;
}
void report_warning(void *message) { CHECK(message); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    warnings++;
    return true;
}
static void report_options(bool newopt)
{
    (void)newopt;
    options++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Probe relay") == 0 && strcmp(version, "0.02") == 0);
    reports++;
}
void prepare_relays(void)
{
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.probe.select = select_probe;
    hal.probe.get_state = probe_state;
    hal.delay_ms = delay;
    hal.driver_cap.toolsetter = native_toolsetter;
    hal.driver_cap.probe2 = native_probe2;
    grbl.on_report_options = report_options;
}
void initialize_relays(void)
{
    void probe_select_init(void);
    probe_select_init();
}
void load_relays(void)
{
    prepare_relays();
    initialize_relays();
    CHECK(relay_details && relay_details->n_settings == 2);
    relay_details->load();
}
const setting_detail_t *relay_setting(setting_id_t id)
{
    CHECK(relay_details);
    for (unsigned i = 0; i < relay_details->n_settings; i++)
        if (relay_details->settings[i].id == id)
            return &relay_details->settings[i];
    CHECK(false);
    return NULL;
}
void set_relay_port(setting_id_t id, float port)
{
    const setting_detail_t *setting = relay_setting(id);
    CHECK(((setting_set_float_ptr)setting->value)(id, port) == Status_OK);
}
float get_relay_port(setting_id_t id)
{
    const setting_detail_t *setting = relay_setting(id);
    return ((setting_get_float_ptr)setting->get_value)(id);
}
