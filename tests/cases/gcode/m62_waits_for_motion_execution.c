#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M62P0") == Status_OK);
    CHECK(output_calls == 0);
    queue_motion_program("G1X1F100");
    CHECK(output_calls == 0);
    execute_motion_program();
    CHECK(output_calls == 1);
    CHECK(output_pin_log[0] == 0 && output_log[0]);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
