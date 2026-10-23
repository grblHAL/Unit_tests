#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(N_AXIS == 8);
    CHECK(named_parameter_block("G21") == Status_OK);
    NEAR(read_named_parameter("_abs_w"), 0);
    NEAR(read_named_parameter("_w"), 0);
    CHECK(named_parameter_block("G20") == Status_OK);
    NEAR(read_named_parameter("_abs_w"), 0);
    NEAR(read_named_parameter("_w"), 0);
    return EXIT_SUCCESS;
}
