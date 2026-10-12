#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("F125") == Status_OK);
    NEAR(read_named_parameter("_feed"), 125);
    CHECK(named_parameter_block("F250") == Status_OK);
    NEAR(read_named_parameter("_feed"), 250);
    return EXIT_SUCCESS;
}
