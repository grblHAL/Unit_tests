#include "rgb_host.h"
int main(void)
{
 prepare_rgb(true);
 parser_block_t block = {0}; block.user_mcode = RGB_WriteLEDs;
 block.words.r = block.words.u = On; block.values.r = 80; block.values.u = 30;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 block.words.u = Off; block.words.k = block.words.i = On; block.values.r = 90; block.values.ijk[0] = 2;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(last_mask.R && !last_mask.G && !last_mask.B && !last_mask.W);
 CHECK(colors[0][2].R == 90 && colors[0][2].G == 30); CHECK(colors[0][0].R == 80);
 return 0;
}
