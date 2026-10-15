#include "support/io_motion_host.h"
int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M62P0") == Status_OK);
    CHECK(io_block("M62P1") == Status_OK);
    CHECK(io_block("M63P0") == Status_OK);
    CHECK(output_calls == 0);
    queue_motion_program("G1X1F100");
    CHECK(output_calls == 0);
    execute_motion_program();
    CHECK(output_calls == 3);
    CHECK(output_pin_log[0] == 0 && output_log[0]);
    CHECK(output_pin_log[1] == 1 && output_log[1]);
    CHECK(output_pin_log[2] == 0 && !output_log[2]);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
