#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M68E1Q125") == Status_OK);
    CHECK(analog_output_calls == 1);
    CHECK(analog_output_port == 1);
    CHECK(fabsf(analog_output_value - 125.0f) < 0.00001f);
    return EXIT_SUCCESS;
}
