#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G20") == Status_OK);
    NEAR(read_named_parameter("_imperial"), 1);
    NEAR(read_named_parameter("_metric"), 0);
    CHECK(named_parameter_block("G21") == Status_OK);
    NEAR(read_named_parameter("_imperial"), 0);
    NEAR(read_named_parameter("_metric"), 1);
    return EXIT_SUCCESS;
}
