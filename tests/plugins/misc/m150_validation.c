#include "rgb_host.h"
int main(void)
{
 prepare_rgb(false); CHECK(grbl.user_mcode.check(RGB_WriteLEDs) == UserMCode_NoValueWords);
 parser_block_t block = {0}; block.user_mcode = RGB_WriteLEDs;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueWordMissing);
 block.words.r = On; block.values.r = 42.5f;
 CHECK(grbl.user_mcode.validate(&block) == Status_BadNumberFormat);
 block.values.r = 256; CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block.values.r = 200; block.words.i = On; block.values.ijk[0] = 3;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block.words.r = On; block.values.ijk[0] = 2; block.words.s = On; block.values.s = 2;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block.values.s = 0; CHECK(grbl.user_mcode.validate(&block) == Status_OK);
 CHECK(!block.words.r && !block.words.i && !block.words.s); CHECK(rgb_calls[0] == 0 && rgb_calls[1] == 0);
 return 0;
}
