#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_output[0] = 0;
    parser_block_t block = {.user_mcode = Trinamic_DebugReport, .words.y = On};
    CHECK(tmc_command(&block) == Status_OK);
    CHECK(strstr(tmc_output, " Y = 0x"));
    CHECK(!strstr(tmc_output, " X = 0x") && !strstr(tmc_output, " Z = 0x"));
    return 0;
}
