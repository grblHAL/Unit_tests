#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_SetPinState;
 CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueWordMissing);
 block.words.p = block.words.s = On; block.values.p = 2; block.values.s = 1;
 parser_block_t validated = block; CHECK(grbl.user_mcode.validate(&validated) == Status_OK && !validated.words.p && !validated.words.s);
 grbl.user_mcode.execute(STATE_CHECK_MODE, &block); CHECK(output_calls == 0);
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(digital_outputs[2] && !digital_outputs[0] && output_calls == 1);
 block.values.s = 0; grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(!digital_outputs[2] && output_calls == 2);
 block.values.p = 3; CHECK(grbl.user_mcode.validate(&block) != Status_OK); CHECK(output_calls == 2);
 return 0;
}
