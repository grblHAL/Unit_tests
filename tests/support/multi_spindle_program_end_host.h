#pragma once
#include "support/spindle_multi_override_host.h"
static coolant_state_t end_coolant;
static unsigned end_notifications;
static program_flow_t end_flow;
static void end_set_coolant(coolant_state_t state) { end_coolant = state; }
static coolant_state_t end_get_coolant(void) { return end_coolant; }
static void end_completed(program_flow_t flow, bool check_mode)
{
    CHECK(!check_mode);
    end_notifications++;
    end_flow = flow;
}
static inline void prepare_multi_spindle_program_end(bool restore)
{
    prepare_independent_spindle_overrides();
    hal.coolant_cap.flood = true;
    hal.coolant.set_state = end_set_coolant;
    hal.coolant.get_state = end_get_coolant;
    grbl.on_program_completed = end_completed;
    const setting_detail_t *actions = setting_get_details(Setting_RestoreOverrides, NULL);
    CHECK(actions != NULL);
    /* Keep these shutdown tests' G54 policy while varying override restoration. */
    char value[] = {(char)((actions->datatype == Format_Bitfield ? '2' : '0') + restore), '\0'};
    CHECK(settings_store_setting(Setting_RestoreOverrides, value) == Status_OK);
    plan_feed_override(75, 50);
    CHECK(spindle_program_block("M8") == Status_OK && end_coolant.flood);
}
static inline void check_multi_spindle_program_end(bool restore, program_flow_t flow)
{
    CHECK(end_notifications == 1 && end_flow == flow);
    CHECK(!end_coolant.flood && !gc_state.modal.coolant.flood);
    CHECK(sys.override.feed_rate == (restore ? 100 : 75));
    CHECK(sys.override.rapid_rate == (restore ? 100 : 50));
    for(unsigned slot = 0; slot < 2; slot++) {
        CHECK(!actual_spindle_states[slot].on);
        CHECK(!gc_state.modal.spindle[slot].state.on);
        CHECK(spindle_get(slot)->param->override_pct == (restore ? 100 : (slot ? 120 : 110)));
    }
    CHECK(spindle_output_calls[2] == 0);
}
