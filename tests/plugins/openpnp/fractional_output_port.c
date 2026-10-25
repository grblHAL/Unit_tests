#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_SetPinState;
 block.words.p = block.words.s = On; block.values.p = 0.5f; block.values.s = 1;
 CHECK(grbl.user_mcode.validate(&block) != Status_OK); CHECK(output_calls == 0); return 0;
}
