#include "misc_host.h"
int main(void)
{
 prepare_m220();
 parser_block_t block = {0}; block.user_mcode = (user_mcode_t)999;
 CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(previous_checks == 1 && previous_validations == 1 && previous_executions == 1);
 grbl.on_report_options(true); CHECK(previous_reports == 1 && plugin_reports == 0);
 grbl.on_report_options(false); CHECK(previous_reports == 2 && plugin_reports == 1);
 CHECK(override_calls == 0);
 return 0;
}
