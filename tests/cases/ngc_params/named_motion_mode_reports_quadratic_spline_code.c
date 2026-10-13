#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G5.1X1Y1I0J1F100") == Status_OK);
    float value = read_named_parameter("_motion_mode");
    fprintf(stderr, "G5.1: _motion_mode=%g, expected 51\n", value);
    NEAR(value, 51);
    return EXIT_SUCCESS;
}
