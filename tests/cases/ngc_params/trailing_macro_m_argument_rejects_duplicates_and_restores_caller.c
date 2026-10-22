#include "support/macro_m_argument_host.h"
#include "support/queued_motion_rejection_host.h"

int main(void)
{
    prepare_motion_program();
    grbl.on_macro_execute = capture_m_argument;
    CHECK(ngc_param_set(13, 99));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G65P100M3M8", Status_GcodeWordRepeated);
    CHECK(macro_calls == 0 && ngc_call_level() == 0);
    CHECK(!gc_spindle_get(0)->state.on && gc_state.modal.coolant.mask == 0);
    CHECK(macro_block("G65P100M8") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_scope == 1 && macro_words.m);
    NEAR(macro_m_argument, 8);
    float parent;
    CHECK(ngc_param_get(13, &parent));
    NEAR(parent, 99);
    CHECK(ngc_call_level() == 0 && plan_get_current_block() == NULL);
    CHECK(!gc_spindle_get(0)->state.on && gc_state.modal.coolant.mask == 0);
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
