#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(N_AXIS == 8);
    const char *names[] = {"_abs_a", "_abs_b", "_abs_c", "_abs_u", "_abs_v"};
    settings.steppers.is_rotary.mask = (1u << 3) | (1u << 4) | (1u << 5);
    CHECK(named_parameter_block("G20") == Status_OK);
    for(unsigned i = 0; i < 5; i++) {
        settings.axis[i + 3].steps_per_mm = 100;
        sys.position[i + 3] = 2540;
        NEAR(read_named_parameter(names[i]), i < 3 ? 25.4f : 1.0f);
    }
    CHECK(named_parameter_block("G21") == Status_OK);
    for(unsigned i = 0; i < 5; i++)
        NEAR(read_named_parameter(names[i]), 25.4f);
    return EXIT_SUCCESS;
}
