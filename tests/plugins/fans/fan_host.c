#include "fan_host.h"
setting_details_t *registered_settings;
unsigned available_ports = 2, warnings, reset_calls, completed_calls, spindle_calls, output_calls, reports, saved;
bool alloc_ok = true, claims_ok = true, outputs[2];
char fan_output[256];
foreground_task_ptr delayed_task;
void *delayed_data;
uint32_t delayed_ms;
static uint8_t nvs[64];
static size_t nvs_size;
static void output(const char *text) { CHECK(strlen(fan_output) + strlen(text) < sizeof(fan_output)); strcat(fan_output, text); }
static void reset(void) { reset_calls++; }
static void completed(program_flow_t flow, bool check) { (void)flow; CHECK(!check); completed_calls++; }
static nvs_transfer_result_t read_nvs(uint8_t *dest, uint32_t address, uint32_t size, bool checksum)
{ CHECK(address == 2048 && size <= sizeof(nvs) && checksum); if(!saved) return false; CHECK(size == nvs_size); memcpy(dest, nvs, size); return true; }
static nvs_transfer_result_t write_nvs(uint32_t address, uint8_t *source, uint32_t size, bool checksum)
{ CHECK(address == 2048 && size <= sizeof(nvs) && checksum); memcpy(nvs, source, size); nvs_size = size; saved++; return true; }
nvs_address_t nvs_alloc(size_t size) { CHECK(size <= sizeof(nvs)); return alloc_ok ? 2048 : 0; }
bool settings_register(setting_details_t *details) { CHECK(registered_settings == NULL); registered_settings = details; return true; }
static uint8_t get_next(io_port_cfg_t *config, uint8_t port, const char *description, pin_cap_t caps)
{ (void)caps; CHECK(config->n_ports == 2 && description); return port == IOPORT_UNASSIGNED ? 1 : (uint8_t)(port - 1); }
static xbar_t *claim(io_port_cfg_t *config, uint8_t *port, const char *description, pin_cap_t caps)
{ static xbar_t pin; (void)caps; CHECK(config->n_ports == 2 && *port < 2 && description); return claims_ok ? &pin : NULL; }
static status_code_t set_value(io_port_cfg_t *config, uint8_t *port, pin_cap_t caps, float value)
{ (void)config; (void)caps; CHECK(value >= -1 && value < 2); *port = value < 0 ? IOPORT_UNASSIGNED : (uint8_t)value; return Status_OK; }
static float get_value(io_port_cfg_t *config, uint8_t port) { (void)config; return port == IOPORT_UNASSIGNED ? -1 : port; }
io_port_cfg_t *ioports_cfg(io_port_cfg_t *config, io_port_type_t type, io_port_direction_t dir)
{ CHECK(type == Port_Digital && dir == Port_Output); config->n_ports = available_ports; config->get_next = get_next; config->claim = claim; config->get_value = get_value; config->set_value = set_value; return config; }
bool ioport_digital_out(uint8_t port, uint32_t value) { CHECK(port < 2 && value <= 1); outputs[port] = value; output_calls++; return true; }
bool spindle_enumerate_spindles(spindle_enumerate_callback_ptr callback, void *data) { (void)callback; (void)data; return true; }
void report_warning(void *message) { CHECK(message); }
bool task_run_on_startup(foreground_task_ptr fn, void *data) { CHECK(fn == report_warning && data); warnings++; return true; }
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms) { CHECK(delayed_task == NULL); delayed_task = fn; delayed_data = data; delayed_ms = ms; return true; }
void task_delete(foreground_task_ptr fn, void *data) { if(delayed_task == fn && delayed_data == data) { delayed_task = NULL; delayed_data = NULL; delayed_ms = 0; } }
void report_add_realtime(report_tracking_t report) { CHECK(report == Report_Fan); reports++; }
void run_delayed_fan(void) { CHECK(delayed_task); foreground_task_ptr fn = delayed_task; void *data = delayed_data; delayed_task = NULL; fn(data); }
const setting_detail_t *fan_setting(setting_id_t id)
{ CHECK(registered_settings); for(unsigned i = 0; i < registered_settings->n_settings; i++) if(registered_settings->settings[i].id == id) return &registered_settings->settings[i]; CHECK(false); return NULL; }
void prepare_fans(void) { prepare_hooks(); hal.driver_reset = reset; hal.stream.write = output; hal.nvs.memcpy_from_nvs = read_nvs; hal.nvs.memcpy_to_nvs = write_nvs; grbl.on_program_completed = completed; }
void load_fans(void) { prepare_fans(); fans_init(); CHECK(registered_settings); registered_settings->load(); }
