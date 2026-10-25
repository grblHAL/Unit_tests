#include "openpnp_host.h"
int main(void)
{
 prepare_openpnp(); gc_state.position[X_AXIS] = 12; gc_state.position[Y_AXIS] = 25; gc_state.position[Z_AXIS] = 6;
 offsets[X_AXIS] = 2; offsets[Y_AXIS] = 5; offsets[Z_AXIS] = 1;
 sys.position[X_AXIS] = 1600; sys.position[Y_AXIS] = 2400; sys.position[Z_AXIS] = 800;
 parser_block_t block = {0}; block.user_mcode = OpenPNP_GetCurrentPosition;
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(strstr(pnp_output, "X:10.000 Y:20.000 Z:5.000") != NULL);
 clear_openpnp_output(); block.words.r = block.words.d = On;
 grbl.user_mcode.execute(STATE_IDLE, &block);
 CHECK(strstr(pnp_output, "X:18.000 Y:25.000 Z:9.000") != NULL);
 CHECK(strstr(pnp_output, "Count X:1600 Y:2400 Z:800") != NULL); return 0;
}
