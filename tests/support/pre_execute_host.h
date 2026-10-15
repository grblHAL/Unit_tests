#pragma once
#include "support/cutter_parser_host.h"
#include "state_machine.h"

static unsigned pre_execute_calls;
static status_code_t pre_execute_result = Status_Unhandled;
static modal_groups_t pre_execute_commands;
static float pre_execute_x, pre_execute_feed;
static bool pre_execute_prior_inches, pre_execute_new_inches;
static status_code_t observe_pre_execute(modal_groups_t *commands, parser_state_t *parser,
                                         parser_block_t *block, spindle_t *spindle)
{
    CHECK(parser == &gc_state && commands != NULL && block != NULL);
    (void)spindle;
    pre_execute_calls++;
    pre_execute_commands = *commands;
    pre_execute_x = block->values.xyz[X_AXIS];
    pre_execute_feed = block->values.f;
    pre_execute_prior_inches = parser->modal.units_imperial;
    pre_execute_new_inches = block->modal.units_imperial;
    return pre_execute_result;
}
static inline void prepare_pre_execute(void)
{
    prepare_cutter_parser();
    settings.arc_tolerance = .02f;
    grbl.on_pre_gcode_execute = observe_pre_execute;
    state_set(STATE_IDLE);
}
