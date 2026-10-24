#include "misc_host.h"
int main(void)
{
 prepare_m220();
 parser_block_t block = {0}; block.user_mcode = SetFeedOverrides;
 block.words.r = On; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(override_calls == 0);
 block.words.r = Off; block.words.b = On; grbl.user_mcode.execute(STATE_IDLE, &block);
 block.words.b = Off; block.words.s = On; block.values.s = 125;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(sys.override.feed_rate == 125 && sys.override.rapid_rate == 100);
 block.words.r = On; block.values.s = 25; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(sys.override.feed_rate == 125 && sys.override.rapid_rate == 25);
 block.words.s = Off; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(sys.override.feed_rate == 100 && sys.override.rapid_rate == 100);
 CHECK(override_calls == 3); CHECK(previous_executions == 0);
 return 0;
}
