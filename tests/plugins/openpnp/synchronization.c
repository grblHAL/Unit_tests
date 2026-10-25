#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); parser_block_t block = {0}; block.user_mcode = OpenPNP_SetAcceleration;
 block.words.t = block.words.p = On; block.values.t = 100; block.values.p = 50;
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(synchronizations == 1);
 CHECK(accelerations[X_AXIS] == 100 && accelerations[Y_AXIS] == 100 && accelerations[Z_AXIS] == 50);
 block.words.s = On; block.values.s = 200; grbl.user_mcode.execute(STATE_IDLE, &block);
 for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(accelerations[axis] == 200 && acceleration_calls[axis] == 2);
 block = (parser_block_t){0}; block.user_mcode = OpenPNP_FinishMoves; grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(synchronizations == 3);
 block.user_mcode = OpenPNP_SettingsReset; grbl.user_mcode.execute(STATE_IDLE, &block);
 for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(accelerations[axis] == 0 && acceleration_calls[axis] == 3);
 CHECK(synchronizations == 4 && output_calls == 0); return 0;
}
