#include "support/analog_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M67E0Q25") == Status_OK);
    CHECK(io_block("M67E1Q75") == Status_OK);
    CHECK(io_block("M67E0Q50") == Status_OK);
    CHECK(analog_output_calls == 0);
    queue_motion_program("G1X1F100");
    CHECK(analog_output_calls == 0);
    execute_motion_program();
    CHECK(analog_output_calls == 3);
    CHECK(analog_output_port_log[0] == 0 && analog_output_port_log[1] == 1 && analog_output_port_log[2] == 0);
    NEAR(analog_output_value_log[0], 25);
    NEAR(analog_output_value_log[1], 75);
    NEAR(analog_output_value_log[2], 50);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
