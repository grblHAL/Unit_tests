#include "odometer_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
uint32_t odometer_ticks = 100;
unsigned odometer_pulse_counts[N_AXIS], odometer_state_calls, odometer_spindle_calls, odometer_settings_calls, odometer_selected_calls, odometer_task_count, odometer_warnings;
unsigned odometer_alternate_calls;
bool odometer_replace_pulse;
char odometer_output[2048];
sys_commands_t *odometer_commands;
static foreground_task_ptr tasks[4];
static void *task_data[4];
bool protocol_execute_realtime(void) { CHECK(false); return false; }
bool protocol_exec_rt_system(void) { CHECK(false); return false; }
bool state_door_reopened(void) { CHECK(false); return false; }
static void pulse(stepper_t *stepper)
{ for(unsigned axis = 0; axis < N_AXIS; axis++) if(stepper->step_out.mask & (1U << axis)) odometer_pulse_counts[axis]++; }
static void alternate_pulse(stepper_t *stepper) { odometer_alternate_calls++; pulse(stepper); }
static uint32_t ticks(void) { return odometer_ticks; }
static void state_changed(sys_state_t state) { (void)state; odometer_state_calls++; }
static void settings_changed(settings_t *value, settings_changed_flags_t flags)
{ (void)flags; CHECK(value == &settings); odometer_settings_calls++; if(odometer_replace_pulse) hal.stepper.pulse_start = alternate_pulse; }
static void selected(spindle_ptrs_t *spindle) { CHECK(spindle); odometer_selected_calls++; }
static void write_output(const char *text) { CHECK(strlen(odometer_output) + strlen(text) < sizeof(odometer_output)); strcat(odometer_output, text); }
static void report_options(bool newopt) { (void)newopt; }
void report_message(const char *message, message_type_t type)
{ CHECK(type == Message_Plain || type == Message_Warning); write_output(message); write_output("\n"); }
void report_plugin(const char *name, const char *version) { CHECK(strcmp(name, "Odometers") == 0 && strlen(version)); write_output(name); }
void report_warning(void *message) { CHECK(message); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{ CHECK(fn == report_warning && data); odometer_warnings++; return true; }
bool task_add_immediate(foreground_task_ptr fn, void *data)
{ CHECK(odometer_task_count < 4); tasks[odometer_task_count] = fn; task_data[odometer_task_count++] = data; return true; }
void system_register_commands(sys_commands_t *commands)
{ CHECK(odometer_commands == NULL && commands->n_commands == 1 && strcmp(commands->commands[0].command, "ODOMETERS") == 0); odometer_commands = commands; }
status_code_t odometer_query(char *args)
{ CHECK(odometer_commands); return odometer_commands->commands[0].execute(STATE_IDLE, args); }
void odometer_clear_output(void) { odometer_output[0] = 0; }
void odometer_driver_spindle(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ CHECK(spindle && (rpm == 500 || rpm == 0)); (void)state; odometer_spindle_calls++; }
void odometer_run_tasks(void)
{ unsigned count = odometer_task_count; odometer_task_count = 0; for(unsigned i = 0; i < count; i++) tasks[i](task_data[i]); }
void odometer_prepare(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init()); hal.get_elapsed_ticks = ticks; hal.stepper.pulse_start = pulse; hal.stream.write = write_output;
 grbl.on_state_change = state_changed; grbl.on_settings_changed = settings_changed; grbl.on_spindle_selected = selected; grbl.on_report_options = report_options;
 for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].steps_per_mm = 80;
}
void odometer_move(uint32_t x, uint32_t y, uint32_t z, uint32_t duration)
{
 uint32_t steps[] = {x,y,z}; grbl.on_state_change(STATE_CYCLE);
 for(unsigned axis = 0; axis < 3; axis++) {
  stepper_t stepper = {0}; stepper.step_out.mask = 1U << axis;
  for(uint32_t i = 0; i < steps[axis]; i++) hal.stepper.pulse_start(&stepper);
 }
 odometer_ticks += duration; grbl.on_state_change(STATE_IDLE);
}
