#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    unsigned before = tmc_writes;
    uint32_t chopconf = tmc_registers[0][TMC2209Reg_CHOPCONF];
    parser_block_t off = {.user_mcode = Trinamic_ChopperTiming, .words.x = On, .words.o = On};
    off.values.o = 0;
    CHECK(tmc_command(&off) == Status_GcodeValueOutOfRange);
    parser_block_t end = {.user_mcode = Trinamic_ChopperTiming, .words.x = On, .words.p = On};
    end.values.p = 12.5f;
    CHECK(tmc_command(&end) == Status_GcodeValueOutOfRange);
    parser_block_t start = {.user_mcode = Trinamic_ChopperTiming, .words.x = On, .words.s = On};
    start.values.s = 9;
    CHECK(tmc_command(&start) == Status_GcodeValueOutOfRange);
    CHECK(tmc_writes == before && tmc_registers[0][TMC2209Reg_CHOPCONF] == chopconf);
    return 0;
}
