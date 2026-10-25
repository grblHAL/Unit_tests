#include "support/multi_spindle_modal_host.h"
static coolant_state_t coolant_off(void) { return (coolant_state_t){0}; }
static void keep_coolant_off(coolant_state_t state) { CHECK(state.value == 0); }

int main(void)
{
    modal_secondary_enabled = false;
    prepare_multi_spindle_modal_program();
    hal.coolant.get_state = coolant_off;
    hal.coolant.set_state = keep_coolant_off;
    CHECK(spindle_get(0) != NULL && spindle_get(1) == NULL);
    CHECK(gc_state.modal.spindle[1].hal == NULL);
    const setting_detail_t *actions = setting_get_details(Setting_RestoreOverrides, NULL);
    CHECK(actions != NULL);
    char restore[] = {(char)(actions->datatype == Format_Bitfield ? '3' : '1'), '\0'};
    CHECK(settings_store_setting(Setting_RestoreOverrides, restore) == Status_OK);
    CHECK(spindle_program_block("M3S6000") == Status_OK);
    spindle_set_override(spindle_get(0), 150);
    CHECK(actual_spindle_states[0].on);
    CHECK(fabsf(actual_spindle_rpm[0] - 9000.0f) < 0.01f);
    CHECK(spindle_program_block("M2") == Status_OK);
    CHECK(!actual_spindle_states[0].on);
    CHECK(spindle_get(0)->param->override_pct == 100);
    CHECK(spindle_program_block("M3S4000") == Status_OK);
    CHECK(actual_spindle_states[0].on);
    NEAR(actual_spindle_rpm[0], 4000);
    CHECK(spindle_program_block("M30") == Status_OK);
    CHECK(!actual_spindle_states[0].on);
    CHECK(gc_state.modal.spindle[1].hal == NULL && spindle_get(1) == NULL);
    CHECK(spindle_output_calls[1] == 0 && spindle_output_calls[2] == 0);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
