#include "misc_host.h"
system_t sys;
grbl_hal_t hal;
/* nuts_bolts links delay helpers too; M220 must never call them. */
bool protocol_execute_realtime(void) { CHECK(false); return false; }
bool protocol_exec_rt_system(void) { CHECK(false); return false; }
bool state_door_reopened(void) { CHECK(false); return false; }
grbl_t grbl;
unsigned override_calls, previous_checks, previous_validations, previous_executions, previous_reports, plugin_reports;
char reported_plugin[80];
void plan_feed_override(override_t feed, override_t rapid)
{ override_calls++; sys.override.feed_rate = feed; sys.override.rapid_rate = rapid; }
void report_plugin(const char *name, const char *version)
{ CHECK(strlen(name) < sizeof(reported_plugin)); strcpy(reported_plugin, name); CHECK(strlen(version) > 0); plugin_reports++; }
static user_mcode_type_t previous_check(user_mcode_t code)
{ CHECK(code != SetFeedOverrides); previous_checks++; return UserMCode_Normal; }
static status_code_t previous_validate(parser_block_t *block)
{ CHECK(block->user_mcode != SetFeedOverrides); previous_validations++; return Status_GcodeValueOutOfRange; }
static void previous_execute(sys_state_t state, parser_block_t *block)
{ CHECK(state == STATE_IDLE); CHECK(block->user_mcode != SetFeedOverrides); previous_executions++; }
static void previous_report(bool newopt) { (void)newopt; previous_reports++; }
void prepare_hooks(void)
{
 sys.override.feed_rate = 100; sys.override.rapid_rate = 100;
 grbl.user_mcode.check = previous_check;
 grbl.user_mcode.validate = previous_validate;
 grbl.user_mcode.execute = previous_execute;
 grbl.on_report_options = previous_report;

}
