#pragma once
#include "support/rtcp_host.h"
static unsigned delegated_checks, delegated_validations, delegated_executions;
static uint_fast16_t delegated_state;
static parser_block_t *delegated_block;
static user_mcode_type_t delegate_check(user_mcode_t code)
{ delegated_checks++; CHECK(code == 900); return UserMCode_Normal; }
static status_code_t delegate_validate(parser_block_t *block)
{ delegated_validations++; delegated_block = block; return Status_GcodeValueWordMissing; }
static void delegate_execute(uint_fast16_t state, parser_block_t *block)
{ delegated_executions++; delegated_state = state; delegated_block = block; }
static inline void prepare_rtcp_routing(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    grbl.user_mcode.check = delegate_check;
    grbl.user_mcode.validate = delegate_validate;
    grbl.user_mcode.execute = delegate_execute;
    rtcp_ac_init();
}
