#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_GetADCScaled; block.words.e = On; block.values.e = 8;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block.values.e = 0.5f; CHECK(grbl.user_mcode.validate(&block) == Status_GcodeCommandValueNotInteger);
 block.values.e = 7; CHECK(grbl.user_mcode.validate(&block) == Status_OK && !block.words.e);
 block = (parser_block_t){0}; block.user_mcode = OpenPNP_GetPinState; block.words.p = On; block.values.p = 2;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueOutOfRange);
 block.values.p = 1; CHECK(grbl.user_mcode.validate(&block) == Status_OK && !block.words.p);
 block = (parser_block_t){0}; block.user_mcode = OpenPNP_SetADCScaling; block.words.e = On;
 CHECK(grbl.user_mcode.validate(&block) != Status_OK); CHECK(input_calls == 0 && output_calls == 0);
 return 0;
}
