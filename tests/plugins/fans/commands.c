#include "fan_host.h"
int main(void)
{
 load_fans(); CHECK(saved == 1 && warnings == 0);
 CHECK(grbl.user_mcode.check(Fan_On) == UserMCode_Normal && grbl.user_mcode.check(Fan_Off) == UserMCode_Normal);
 parser_block_t block = {0}; block.user_mcode = Fan_On; block.words.p = On; block.values.p = 1;
 parser_block_t validated = block; CHECK(grbl.user_mcode.validate(&validated) == Status_OK && !validated.words.p);
 grbl.user_mcode.execute(STATE_CHECK_MODE, &block); CHECK(output_calls == 0);
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(fan_get_state(1) && outputs[1] && !outputs[0]);
 block.user_mcode = Fan_Off; grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(!fan_get_state(1) && !outputs[1]);
 block.values.p = 0.5f; CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 CHECK(reports == 2); return 0;
}
