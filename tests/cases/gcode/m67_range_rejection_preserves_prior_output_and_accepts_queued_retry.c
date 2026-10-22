#include "support/analog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M67E0Q50") == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    CHECK(io_block("M67E1Q256") == Status_GcodeValueOutOfRange);
    CHECK(plan_get_current_block() == first);
    CHECK(plan_get_block_buffer_available() == available);
    CHECK(analog_output_calls == 0);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(io_block("M67E1Q255") == Status_OK);
    queue_motion_program("G1X2");
    CHECK(analog_output_calls == 0);
    execute_motion_program();
    CHECK(analog_output_calls == 2);
    CHECK(analog_output_port_log[0] == 0 && analog_output_port_log[1] == 1);
    NEAR(analog_output_value_log[0], 50);
    NEAR(analog_output_value_log[1], 255);
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
