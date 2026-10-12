#pragma once
#include "hal.h"
extern sys_state_t host_state;
extern bool host_sync_ok;
extern unsigned host_sync_calls, host_reports, host_reset_calls, host_delay_calls;
extern float host_delay_seconds;
extern delaymode_t host_delay_mode;
