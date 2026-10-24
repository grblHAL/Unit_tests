#include "support/macro_parser_host.h"
#include "support/queued_motion_rejection_host.h"

int main(void)
{
    prepare_motion_program();
    grbl.on_macro_execute = capture_macro;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *commands[] = {"G65.1P100", "G66.2P100"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        CHECK(macro_block(commands[i]) == Status_GcodeUnsupportedCommand);
        CHECK(macro_calls == 0 && ngc_call_level() == 0 && gc_state.g66_args == NULL);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        NEAR(gc_state.position[X_AXIS], 1);
    }
    CHECK(macro_block("G65P100A7") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_scope == 1 && ngc_call_level() == 0);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
