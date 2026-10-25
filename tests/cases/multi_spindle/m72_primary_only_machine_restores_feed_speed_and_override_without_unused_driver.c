#include "support/multi_spindle_modal_host.h"
int main(void)
{
    modal_secondary_enabled = false;
    prepare_multi_spindle_modal_program();
    CHECK(spindle_get(1) == NULL && gc_state.modal.spindle[1].hal == NULL);
    CHECK(spindle_program_block("M3S3000F120") == Status_OK);
    spindle_set_override(spindle_get(0), 120);
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(spindle_program_block("M5S5000F240") == Status_OK);
    spindle_set_override(spindle_get(0), 80);
    CHECK(!actual_spindle_states[0].on);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    NEAR(gc_state.feed_rate, 120);
    NEAR(gc_state.modal.spindle[0].rpm, 3000);
    CHECK(spindle_get(0)->param->override_pct == 120);
    CHECK(fabsf(actual_spindle_rpm[0] - 3600) < .01f);
    CHECK(spindle_get(1) == NULL && gc_state.modal.spindle[1].hal == NULL);
    CHECK(spindle_output_calls[1] == 0 && spindle_output_calls[2] == 0);
    CHECK(modal_rpm_update_calls[1] == 0 && modal_rpm_update_calls[2] == 0);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    CHECK(spindle_program_block("M71") == Status_OK);
    return EXIT_SUCCESS;
}
