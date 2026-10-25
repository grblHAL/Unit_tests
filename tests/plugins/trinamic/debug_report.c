#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_output[0] = 0;
    parser_block_t block = {.user_mcode = Trinamic_DebugReport};
    CHECK(tmc_command(&block) == Status_OK);
    CHECK(strstr(tmc_output, "[TRINAMIC]") && strstr(tmc_output, "TMC2209"));
    CHECK(strstr(tmc_output, "Set current") && strstr(tmc_output, "msteps"));
    CHECK(strstr(tmc_output, "STATUS REGISTERS:"));
    CHECK(strstr(tmc_output, " X = 0x") && strstr(tmc_output, " Y = 0x") &&
          strstr(tmc_output, " Z = 0x"));
    return 0;
}
