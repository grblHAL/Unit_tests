#include "support/io_motion_host.h"
int main(void)
{
    prepare_io_motion();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *commands[] = {"M64P-1", "M66P-1L0", "M66P0L5Q1"};
    const status_code_t expected[] = {Status_NegativeValue, Status_NegativeValue, Status_GcodeValueOutOfRange};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        CHECK(io_block(commands[i]) == expected[i]);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(output_calls == 0 && read_calls == 0);
        NEAR(gc_state.position[X_AXIS], 1); NEAR(gc_state.feed_rate, 100);
    }
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(io_block("M64P1") == Status_OK);
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(io_block("M66P0L0") == Status_OK);
    CHECK(read_calls == 1 && physical_input == 0 && input_mode == WaitMode_Immediate);
    return EXIT_SUCCESS;
}
