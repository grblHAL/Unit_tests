#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(N_AXIS == 6);
    const char *names[] = {"_u", "_v", "_w"};
    const char *absolute[] = {"_abs_u", "_abs_v", "_abs_w"};
    for(unsigned i = 0; i < 3; i++) {
        settings.axis[i + 3].steps_per_mm = 100;
        sys.position[i + 3] = (int32_t)(1000 * (i + 1));
        gc_state.position[i + 3] = (float)(10 * (i + 1));
        NEAR(read_named_parameter(names[i]), (float)(10 * (i + 1)));
        NEAR(read_named_parameter(absolute[i]), (float)(10 * (i + 1)));
    }
    CHECK(named_parameter_block("G92U1V2W3") == Status_OK);
    for(unsigned i = 0; i < 3; i++) {
        NEAR(read_named_parameter(names[i]), (float)(i + 1));
        NEAR(read_named_parameter(absolute[i]), (float)(10 * (i + 1)));
    }
    return EXIT_SUCCESS;
}
