#pragma once
#include "misc_host.h"
#include "ioports.h"
#include "task.h"
void prepare_openpnp(void);
void clear_openpnp_output(void);
void openpnp_init(void);
extern unsigned output_calls, input_calls, synchronizations, acceleration_calls[N_AXIS];
extern bool digital_outputs[3];
extern float accelerations[N_AXIS], offsets[N_AXIS];
extern io_port_type_t last_input_type;
extern uint8_t last_input_port;
extern char pnp_output[512];
