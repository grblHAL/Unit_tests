#include "support/canned_motion_host.h"
#include "check.h"
static unsigned return_calls;
static void returned(void)
{
    return_calls++;
    CHECK(plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 80);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Return);
}
int main(void)
{
    prepare_canned_motion();
    grbl.on_macro_return = returned;
    CHECK(canned_block("G1X1F100") == Status_OK);
    CHECK(plan_get_current_block() != NULL);
    CHECK(canned_block("M99") == Status_OK);
    CHECK(return_calls == 1);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    return EXIT_SUCCESS;
}
