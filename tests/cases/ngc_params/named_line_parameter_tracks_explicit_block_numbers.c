#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("N42G21") == Status_OK);
    NEAR(read_named_parameter("_line"), 42);
    CHECK(named_parameter_block("N125G20") == Status_OK);
    NEAR(read_named_parameter("_line"), 125);
    return EXIT_SUCCESS;
}
