#include "support/macro_parser_host.h"
#include "support/motion_program_host.h"
#include "support/tracked_malloc_host.h"
int main(void)
{
    prepare_motion_program();
    grbl.on_macro_execute = capture_macro;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    observe_allocation_heap = true;
    allocation_heap_reject = 1;
    status_code_t status = macro_block("G66P100X7");
    observe_allocation_heap = false;
    CHECK(status == Status_FlowControlStackOverflow);
    CHECK(allocation_heap_calls == 1 && allocation_heap_failures == 1);
    CHECK(macro_calls == 0 && gc_state.g66_args == NULL && ngc_call_level() == 0);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(macro_block("G66P100X7") == Status_OK);
    CHECK(macro_calls == 0);
    queue_motion_program("G1X2F100");
    CHECK(macro_calls == 1 && called_macro == 100 && macro_scope == 1);
    NEAR(macro_x, 7);
    CHECK(macro_block("G67") == Status_OK);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
