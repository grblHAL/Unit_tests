#include "rgb_host.h"
int main(void)
{
 prepare_rgb(false, true);
 parser_block_t block = {0}; block.user_mcode = RGB_WriteLEDs; block.words.w = block.words.i = On;
 block.values.w = 120; block.values.ijk[0] = 0;
 parser_block_t validated = block; CHECK(grbl.user_mcode.validate(&validated) == Status_OK && !validated.words.w);
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(colors[0][0].W == 120 && colors[0][0].R == 0);
 block.values.w = 90; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(colors[0][0].W == 90 && colors[0][0].R == 0);
 block.user_mcode = (user_mcode_t)999;
 CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange); grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(previous_checks == 1 && previous_validations == 1 && previous_executions == 1);
 grbl.on_report_options(false); CHECK(strcmp(reported_plugin, "RGB LED strips (M150)") == 0); return 0;
}
