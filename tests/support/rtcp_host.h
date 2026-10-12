#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void rtcp_ac_init(void);
static inline void prepare_rtcp(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    rtcp_ac_init();
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Setting_Kinematics0, &details) != NULL);
    CHECK(details && details->restore && details->load);
    details->restore();
    details->load();
    CHECK(plan_reset());
}
static inline void zero_rtcp_centers(void)
{
    for(unsigned index = 0; index < 6; index++) {
        char zero[] = "0";
        CHECK(settings_store_setting(Setting_Kinematics0 + index, zero) == Status_OK);
    }
}
static inline void rtcp_command(unsigned code)
{
    parser_block_t block = {.user_mcode = (user_mcode_t)code};
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    CHECK(block.user_mcode_sync);
    grbl.user_mcode.execute(STATE_IDLE, &block);
}
