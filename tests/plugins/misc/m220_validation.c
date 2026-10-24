#include <math.h>
#include "misc_host.h"
static void check_speed(float value, bool rapid, status_code_t expected)
{
 parser_block_t block = {0}; block.user_mcode = SetFeedOverrides;
 block.words.s = On; block.words.r = rapid; block.values.s = value; block.values.r = NAN;
 CHECK(grbl.user_mcode.validate(&block) == expected);
 CHECK(block.user_mcode_sync); CHECK(!block.words.s && !block.words.r);
 CHECK(override_calls == 0); CHECK(sys.override.feed_rate == 100 && sys.override.rapid_rate == 100);
}
int main(void)
{
 prepare_m220();
 CHECK(grbl.user_mcode.check(SetFeedOverrides) == UserMCode_NoValueWords);
 check_speed(125, false, Status_OK); check_speed(25, true, Status_OK);
 check_speed(100.5f, false, Status_BadNumberFormat);
 check_speed(MIN_FEED_RATE_OVERRIDE - 1, false, Status_GcodeValueOutOfRange);
 check_speed(MAX_FEED_RATE_OVERRIDE + 1, false, Status_GcodeValueOutOfRange);
 check_speed(4, true, Status_GcodeValueOutOfRange); check_speed(101, true, Status_GcodeValueOutOfRange);
 parser_block_t block = {0}; block.user_mcode = SetFeedOverrides; block.words.b = On; block.values.b = 1;
 CHECK(grbl.user_mcode.validate(&block) == Status_BadNumberFormat);
 block = (parser_block_t){0}; block.user_mcode = SetFeedOverrides; block.words.r = On; block.values.r = 1;
 CHECK(grbl.user_mcode.validate(&block) == Status_BadNumberFormat);
 return 0;
}
