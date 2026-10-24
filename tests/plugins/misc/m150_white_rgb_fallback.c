#include "rgb_host.h"
int main(void)
{
 prepare_rgb(false, false);
 parser_block_t block = {0}; block.user_mcode = RGB_WriteLEDs; block.words.w = On; block.values.w = 90;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(rgb_calls[0] == 3);
 for(unsigned device = 0; device < 3; device++)
  CHECK(colors[0][device].R == 90 && colors[0][device].G == 90 && colors[0][device].B == 90 && colors[0][device].W == 0);
 return 0;
}
