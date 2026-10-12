#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M67E0Q50") == Status_OK);
    CHECK(analog_output_calls == 0);
    queue_motion_program("G1X1F100");
    CHECK(analog_output_calls == 0);
    execute_motion_program();
    CHECK(analog_output_calls == 1);
    CHECK(analog_output_port == 0);
    CHECK(fabsf(analog_output_value - 50.0f) < 0.00001f);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
