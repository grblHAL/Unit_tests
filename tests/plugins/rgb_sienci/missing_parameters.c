#include "rgb_host.h"
int main(void)
{
    rgb_start();
    parser_block_t block = {0};
    block.user_mcode = RGB_Inspection_Light;
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    CHECK(block.values.q == -1 && block.values.s == -1 && block.user_mcode_sync);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    rgb_expect(0, 255, 255, 255);
    return 0;
}
