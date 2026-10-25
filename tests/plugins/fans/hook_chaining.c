#include "fan_host.h"
static unsigned realtime_calls, accessory_calls;
static void realtime(stream_write_ptr write, report_tracking_flags_t flags)
{ (void)flags; realtime_calls++; write("|Previous:1"); }
static void accessory(uint8_t command) { CHECK(command == 1); accessory_calls++; }
int main(void)
{
 prepare_fans(); grbl.on_realtime_report = realtime; grbl.on_unknown_accessory_override = accessory;
 fans_init(); CHECK(registered_settings); registered_settings->load();
 parser_block_t block = {0}; block.user_mcode = (user_mcode_t)999;
 CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange); grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(previous_checks == 1 && previous_validations == 1 && previous_executions == 1);
 grbl.on_unknown_accessory_override(1); CHECK(accessory_calls == 1);
 fan_output[0] = 0; grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
 CHECK(realtime_calls == 1 && strcmp(fan_output, "|Previous:1") == 0);
 return 0;
}
