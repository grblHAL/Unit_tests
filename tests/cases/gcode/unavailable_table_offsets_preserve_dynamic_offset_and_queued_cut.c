#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(grbl.tool_table.n_tools == 0);
    char dynamic[] = "G43.1Z2";
    CHECK(gc_execute_block(dynamic) == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *commands[] = {"G43H1", "G43.2H1"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        char block[24]; strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
        NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2);
        NEAR(gc_state.position[X_AXIS], 1);
    }
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
