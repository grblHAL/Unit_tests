#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("M50P0") == Status_OK);
    NEAR(read_named_parameter("_feed_override"), 0);
    CHECK(named_parameter_block("M50P1") == Status_OK);
    NEAR(read_named_parameter("_feed_override"), 1);
    return EXIT_SUCCESS;
}
