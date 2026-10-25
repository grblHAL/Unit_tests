#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_GetADCScaled; block.words.e = On; block.values.e = 1;
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(strstr(pnp_output, "A1:128") != NULL); CHECK(last_input_type == Port_Analog);
 parser_block_t scaling = {0}; scaling.user_mcode = OpenPNP_SetADCScaling; scaling.words.e = scaling.words.q = scaling.words.s = On;
 scaling.values.e = 1; scaling.values.s = 0.5f; scaling.values.q = -4;
 parser_block_t validated = scaling; CHECK(grbl.user_mcode.validate(&validated) == Status_OK && !validated.words.e && !validated.words.q && !validated.words.s);
 grbl.user_mcode.execute(STATE_IDLE, &scaling); clear_openpnp_output();
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(strstr(pnp_output, "A1:60") != NULL);
 block.values.e = 0; clear_openpnp_output(); grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(strstr(pnp_output, "A0:128") != NULL);
 block = (parser_block_t){0}; block.user_mcode = OpenPNP_GetPinState; block.words.p = On; block.values.p = 1;
 clear_openpnp_output(); grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(last_input_type == Port_Digital && last_input_port == 1 && strstr(pnp_output, "D1:1") != NULL);
 return 0;
}
