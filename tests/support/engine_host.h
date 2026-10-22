#pragma once
#include "hal.h"
#ifdef HOST_PARSER_FLAGS_API
#define HOST_PARSER_FLAGS gc_state.flags
#else
#define HOST_PARSER_FLAGS gc_state
#endif
/* Call once per test executable. Each executable starts with fresh core statics. */
void engine_prepare(void);
void engine_parser_prepare(void);
void engine_execute_tasks(sys_state_t state);
extern uint32_t engine_ticks;
extern unsigned engine_irq_depth;
extern char engine_output[4096];
