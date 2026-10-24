#include "openpnp_host.h"
parser_state_t gc_state;
unsigned output_calls, input_calls, synchronizations, acceleration_calls[N_AXIS];
bool digital_outputs[3];
float accelerations[N_AXIS], offsets[N_AXIS];
io_port_type_t last_input_type;
uint8_t last_input_port;
char pnp_output[512];
static foreground_task_ptr startup;
static void *startup_data;
static void write_output(const char *text) { CHECK(strlen(pnp_output) + strlen(text) < sizeof(pnp_output)); strcat(pnp_output, text); }
void clear_openpnp_output(void) { pnp_output[0] = 0; }
uint8_t ioports_unclaimed(io_port_type_t type, io_port_direction_t dir)
{ return dir == Port_Output ? 3 : (type == Port_Analog ? 10 : 2); }
bool ioport_digital_out(uint8_t port, uint32_t value)
{ CHECK(port < 3 && value <= 1); digital_outputs[port] = value; output_calls++; return true; }
int32_t ioport_wait_on_input(io_port_type_t type, uint8_t port, wait_mode_t mode, float timeout)
{
 CHECK(mode == WaitMode_Immediate && timeout == 0);
 CHECK(port < (type == Port_Analog ? 8 : 2));
 input_calls++; last_input_type = type; last_input_port = port;
 return type == Port_Analog ? 128 : 1;
}
bool task_run_on_startup(foreground_task_ptr callback, void *data)
{ CHECK(startup == NULL); startup = callback; startup_data = data; return true; }
bool protocol_buffer_synchronize(void) { synchronizations++; return true; }
bool settings_override_acceleration(uint8_t axis, float value)
{ CHECK(axis < N_AXIS && synchronizations > 0); accelerations[axis] = value; acceleration_calls[axis]++; return true; }
float gc_get_offset(uint_fast8_t axis, bool realtime) { CHECK(axis < N_AXIS && realtime); return offsets[axis]; }
void system_convert_array_steps_to_mpos(float *position, int32_t *steps)
{ for(unsigned axis = 0; axis < N_AXIS; axis++) position[axis] = steps[axis] / 80.0f; }
#ifndef _WIN32
char *itoa(int value, char *string, int radix) { CHECK(radix == 10); sprintf(string, "%d", value); return string; }
#endif
void prepare_openpnp(void)
{
 prepare_hooks(); hal.stream.write = write_output; openpnp_init(); CHECK(startup);
 foreground_task_ptr callback = startup; startup = NULL; callback(startup_data);
}
