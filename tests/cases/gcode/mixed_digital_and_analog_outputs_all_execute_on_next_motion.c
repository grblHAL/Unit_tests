#include "support/analog_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M62P0") == Status_OK);
    CHECK(io_block("M67E1Q75") == Status_OK);
    CHECK(io_block("M63P1") == Status_OK);
    CHECK(!output_calls && !analog_output_calls);
    queue_motion_program("G1X1F100");
    CHECK(!output_calls && !analog_output_calls);
    execute_motion_program();
    CHECK(output_calls == 2 && analog_output_calls == 1);
    CHECK(output_pin_log[0] == 0 && output_log[0]);
    CHECK(output_pin_log[1] == 1 && !output_log[1]);
    CHECK(analog_output_port == 1);
    NEAR(analog_output_value, 75);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
