#include "support/lathe_cycle_capture_host.h"
#include "support/named_parameter_host.h"

int main(void)
{
    prepare_lathe_capture();
    CHECK(css_block("G72X10Z20Q7F100") == Status_OK);
    CHECK(lathe_cycle_calls == 1);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G72: _motion_mode=%g, expected 720\n", value);
    NEAR(value, 720);
    return EXIT_SUCCESS;
}
