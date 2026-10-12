#include "support/control_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "motion_control.h"
grbl_hal_t hal;
settings_t settings;
system_t sys;
sys_state_t host_state = STATE_IDLE;
bool host_sync_ok = true;
unsigned host_sync_calls, host_reports, host_reset_calls, host_delay_calls;
float host_delay_seconds;
delaymode_t host_delay_mode;
sys_state_t state_get(void) { return host_state; }
bool protocol_buffer_synchronize(void) { host_sync_calls++; return host_sync_ok; }
void report_add_realtime(report_tracking_t report) { if(report == Report_Coolant) host_reports++; }
void mc_reset(void) { host_reset_calls++; }
