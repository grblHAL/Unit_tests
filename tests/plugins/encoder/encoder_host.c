#include "encoder_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
setting_details_t *encoder_settings;
unsigned encoder_claims, encoder_resets, encoder_configures, encoder_reports, encoder_previous_reports;
bool encoder_storage_ok = true;
static bool encoder_owned[2];
uint8_t encoder_commands[64];
unsigned encoder_command_count;
char encoder_output[1024];
encoder_t encoder_devices[2];
encoder_cfg_t encoder_configs[2];
encoder_on_event_ptr encoder_handlers[2];
static encoder_data_t encoder_data[2];
static void *contexts[2];
static foreground_task_ptr tasks[8];
static void *task_data[8];
static unsigned task_count;
static unsigned index_of(encoder_t *encoder) { CHECK(encoder >= encoder_devices && encoder < encoder_devices + 2); return (unsigned)(encoder - encoder_devices); }
static bool claim(encoder_t *encoder, encoder_on_event_ptr callback, void *context)
{ unsigned index = index_of(encoder); if(encoder_owned[index]) return false; encoder_owned[index] = true; encoder_handlers[index] = callback; contexts[index] = context; encoder_claims++; return true; }
static void reset(encoder_t *encoder) { encoder_data[index_of(encoder)] = (encoder_data_t){0}; encoder_resets++; }
static encoder_data_t *get_data(encoder_t *encoder) { return &encoder_data[index_of(encoder)]; }
static bool configure(encoder_t *encoder, encoder_cfg_t *config) { encoder_configs[index_of(encoder)] = *config; encoder_configures++; return true; }
static bool realtime(uint8_t command) { CHECK(encoder_command_count < 64); encoder_commands[encoder_command_count++] = (uint8_t)command; return true; }
static bool gcode(char *command) { (void)command; CHECK(false); return false; }
static void write_output(const char *text) { CHECK(strlen(encoder_output) + strlen(text) < sizeof(encoder_output)); strcat(encoder_output, text); }
static void previous_report(bool newopt) { (void)newopt; encoder_previous_reports++; }
static void previous_realtime(stream_write_ptr write, report_tracking_flags_t flags) { (void)flags; write("|Previous:1"); }
nvs_address_t nvs_alloc(size_t size) { CHECK(size > 0 && size < 1024); return encoder_storage_ok ? 2048 : 0; }
bool settings_register(setting_details_t *details) { CHECK(!encoder_settings); encoder_settings = details; return true; }
void report_plugin(const char *name, const char *version) { CHECK(strcmp(name, "ENCODER") == 0 && strlen(version)); write_output(name); }
void report_add_realtime(report_tracking_t report) { CHECK(report == Report_Encoder); encoder_reports++; }
bool task_add_immediate(foreground_task_ptr fn, void *data) { CHECK(task_count < 8); tasks[task_count] = fn; task_data[task_count++] = data; return true; }
void task_delete(foreground_task_ptr fn, void *data) { CHECK(fn && data == NULL); }
bool task_add_systick(foreground_task_ptr fn, void *data) { (void)fn; (void)data; CHECK(false); return false; }
void encoder_run_tasks(void) { unsigned count = task_count; task_count = 0; for(unsigned i = 0; i < count; i++) tasks[i](task_data[i]); }
bool protocol_execute_realtime(void) { CHECK(false); return false; }
bool protocol_exec_rt_system(void) { CHECK(false); return false; }
bool state_door_reopened(void) { CHECK(false); return false; }
sys_state_t state_get(void) { CHECK(false); return STATE_IDLE; }
float gc_get_offset(uint_fast8_t axis, bool realtime_value) { (void)axis; (void)realtime_value; CHECK(false); return 0; }
void system_convert_array_steps_to_mpos(float *position, int32_t *steps) { (void)position; (void)steps; CHECK(false); }
void encoder_prepare(unsigned count, bool spindle_first)
{
 CHECK(count <= 2); prepare_eeprom(); CHECK(i2c_eeprom_init()); sys.override.feed_rate = sys.override.rapid_rate = 100;
 hal.stream.write = write_output; grbl.on_report_options = previous_report; grbl.on_realtime_report = previous_realtime;
 grbl.enqueue_realtime_command = realtime; grbl.enqueue_gcode = gcode;
 for(unsigned i = 0; i < count; i++) { encoder_devices[i] = (encoder_t){.caps = {.bidirectional = On, .select = On}, .claim = claim, .reset = reset, .get_data = get_data, .configure = configure}; if(spindle_first && i == 0) encoder_devices[i].caps.spindle_rpm = On; encoder_register(&encoder_devices[i]); }
}
void encoder_load(void) { CHECK(encoder_init() && encoder_settings); encoder_settings->load(); }
void encoder_emit(unsigned index, int32_t position, uint32_t velocity, encoder_event_t event)
{ CHECK(index < 2 && encoder_handlers[index]); encoder_data[index] = (encoder_data_t){position, velocity}; encoder_handlers[index](&encoder_devices[index], &event, contexts[index]); CHECK(event.value == 0); }
static const setting_detail_t *detail(setting_id_t setting)
{ CHECK(encoder_settings); for(unsigned i = 0; i < encoder_settings->n_settings; i++) if(encoder_settings->settings[i].id == setting) return &encoder_settings->settings[i]; CHECK(false); return NULL; }
status_code_t encoder_set(setting_id_t setting, uint_fast16_t value) { return ((setting_set_int_ptr)detail(setting)->value)(setting, value); }
uint32_t encoder_get(setting_id_t setting) { return ((setting_get_int_ptr)detail(setting)->get_value)(setting); }
