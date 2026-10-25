#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    uint32_t before_y = tmc_registers[1][TMC2209Reg_CHOPCONF];
    TMC2209_chopconf_reg_t before_x = {.value = tmc_registers[0][TMC2209Reg_CHOPCONF]};
    parser_block_t block = {.user_mcode = Trinamic_ChopperTiming,
                            .words.x = On,
                            .words.o = On,
                            .words.p = On,
                            .words.s = On};
    block.values.o = 5;
    block.values.p = -1;
    block.values.s = 4;
    CHECK(tmc_command(&block) == Status_OK);
    TMC2209_chopconf_reg_t actual = {.value = tmc_registers[0][TMC2209Reg_CHOPCONF]};
    CHECK(actual.toff == 5 && actual.hend == 2 && actual.hstrt == 3);
    CHECK(actual.mres == before_x.mres && actual.vsense == before_x.vsense);
    CHECK(tmc_registers[1][TMC2209Reg_CHOPCONF] == before_y);
    tmc_output[0] = 0;
    parser_block_t query = {.user_mcode = Trinamic_ChopperTiming};
    CHECK(tmc_command(&query) == Status_OK);
    CHECK(strstr(tmc_output, "[X chopper .toff: 5 .hend: -1 .hstrt: 4]"));
    return 0;
}
