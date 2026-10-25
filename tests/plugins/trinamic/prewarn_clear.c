#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = (TMC2209_drv_status_reg_t){.otpw = 1}.value;
    tmc_registers[1][TMC2209Reg_DRV_STATUS] = (TMC2209_drv_status_reg_t){.ot = 1}.value;
    tmc_output[0] = 0;
    parser_block_t flags = {.user_mcode = Trinamic_ReportPrewarnFlags};
    CHECK(tmc_command(&flags) == Status_OK);
    CHECK(strstr(tmc_output, "[TMCPREWARN:|X:W|Y:O|Z:]"));
    parser_block_t report = {.user_mcode = Trinamic_DebugReport};
    tmc_output[0] = 0;
    CHECK(tmc_command(&report) == Status_OK);
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = 0;
    tmc_registers[1][TMC2209Reg_DRV_STATUS] = 0;
    tmc_output[0] = 0;
    CHECK(tmc_command(&report) == Status_OK);
    const char *row = strstr(tmc_output, "been triggered");
    CHECK(row && strchr(row, '\n'));
    CHECK(strstr(row, "true") && strstr(row, "true") < strchr(row, '\n'));
    parser_block_t clear = {.user_mcode = Trinamic_ClearPrewarnFlags};
    CHECK(tmc_command(&clear) == Status_OK);
    tmc_output[0] = 0;
    CHECK(tmc_command(&report) == Status_OK);
    row = strstr(tmc_output, "been triggered");
    CHECK(row && strchr(row, '\n'));
    CHECK(!strstr(row, "true") || strstr(row, "true") > strchr(row, '\n'));
    CHECK(strstr(row, "false") && strstr(row, "false") < strchr(row, '\n'));
    return 0;
}
