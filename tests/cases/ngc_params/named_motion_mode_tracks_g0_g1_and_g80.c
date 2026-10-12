#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G0") == Status_OK);
    NEAR(read_named_parameter("_motion_mode"), 0);
    CHECK(named_parameter_block("G1F100") == Status_OK);
    NEAR(read_named_parameter("_motion_mode"), 10);
    CHECK(named_parameter_block("G80") == Status_OK);
    NEAR(read_named_parameter("_motion_mode"), 800);
    return EXIT_SUCCESS;
}
