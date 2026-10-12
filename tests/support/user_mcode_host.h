#pragma once
#include "support/engine_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>
static unsigned user_check_calls, user_validate_calls, user_execute_calls;
static parameter_words_t user_claimed;
static parser_block_t user_validated, user_executed;
static sys_state_t user_execution_state;
static status_code_t user_validation_result = Status_OK;
static user_mcode_type_t user_type = UserMCode_Normal;
static bool user_synchronized;
static user_mcode_type_t check_user_mcode(user_mcode_t code) { user_check_calls++; return code == OpenPNP_FinishMoves ? user_type : UserMCode_Unsupported; }
static status_code_t validate_user_mcode(parser_block_t *block) { user_validate_calls++; user_validated = *block; if(user_validation_result != Status_OK) return user_validation_result; block->words.mask &= ~user_claimed.mask; block->user_mcode_sync = user_synchronized; return Status_OK; }
static void execute_user_mcode(sys_state_t state, parser_block_t *block) { user_execute_calls++; user_execution_state = state; user_executed = *block; }
static control_signals_t user_controls(void) { return (control_signals_t){0}; }
static inline void install_user_mcodes(void) { grbl.user_mcode.check = check_user_mcode; grbl.user_mcode.validate = validate_user_mcode; grbl.user_mcode.execute = execute_user_mcode; grbl.on_execute_realtime = protocol_execute_noop; hal.control.get_state = user_controls; state_set(STATE_IDLE); }
static inline void prepare_user_mcodes(void) { engine_parser_prepare(); install_user_mcodes(); }
static inline status_code_t user_mcode_block(const char *text) { char block[96]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text); return gc_execute_block(block); }
