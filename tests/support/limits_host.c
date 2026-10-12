#include "support/control_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "check.h"
grbl_t grbl;
parser_state_t gc_state;
void plan_data_init(plan_line_data_t *data) { (void)data; CHECK(false); }
bool plan_buffer_line(float *target, plan_line_data_t *data) { (void)target; (void)data; CHECK(false); return false; }
void system_convert_array_steps_to_mpos(float *position, int32_t *steps) { (void)position; (void)steps; CHECK(false); }
void st_prep_buffer(void) { CHECK(false); }
void st_wake_up(void) { CHECK(false); }
void st_reset(void) { CHECK(false); }
bool protocol_execute_realtime(void) { CHECK(false); return false; }
bool protocol_exec_rt_system(void) { CHECK(false); return false; }
bool state_door_reopened(void) { CHECK(false); return false; }
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report) { (void)write; (void)report; CHECK(false); }
