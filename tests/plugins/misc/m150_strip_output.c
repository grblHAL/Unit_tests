#include "rgb_host.h"
int main(void)
{
 prepare_rgb(false, false);
 parser_block_t block = {0}; block.user_mcode = RGB_WriteLEDs;
 block.words.r = block.words.u = block.words.b = On; block.values.r = 200; block.values.u = 100; block.values.b = 50;
 grbl.user_mcode.execute(STATE_CHECK_MODE, &block); CHECK(rgb_calls[0] == 0);
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(rgb_calls[0] == 3 && rgb_flushes[0] == 1);
 for(unsigned i = 0; i < 3; i++) CHECK(colors[0][i].R == 200 && colors[0][i].G == 100 && colors[0][i].B == 50);
 block.words.i = block.words.s = block.words.p = On; block.values.ijk[0] = 1; block.values.s = 1; block.values.p = 128;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(rgb_calls[1] == 1 && rgb_flushes[1] == 1); CHECK(colors[1][1].R == 200); CHECK(intensity_calls == 1 && intensity == 128);
 CHECK(rgb_calls[0] == 3);
 block.words.s = Off; grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(colors[0][1].R == 100 && colors[0][1].G == 50 && colors[0][1].B == 25);
 return 0;
}
