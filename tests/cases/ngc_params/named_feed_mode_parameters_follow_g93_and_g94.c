#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G93") == Status_OK);
    NEAR(read_named_parameter("_inverse_time"), 1);
    NEAR(read_named_parameter("_units_per_minute"), 0);
    CHECK(named_parameter_block("G94") == Status_OK);
    NEAR(read_named_parameter("_inverse_time"), 0);
    NEAR(read_named_parameter("_units_per_minute"), 1);
    return EXIT_SUCCESS;
}
