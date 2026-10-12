#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M68E1Q1.25") == Status_OK);
    CHECK(analog_output_calls == 1 && analog_output_port == 1);
    fprintf(stderr, "analog output=%g, expected=1.25\n", (double)analog_output_value);
    CHECK(fabsf(analog_output_value - 1.25f) < 0.00001f);
    return EXIT_SUCCESS;
}
