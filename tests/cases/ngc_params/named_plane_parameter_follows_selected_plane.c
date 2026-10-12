#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G18") == Status_OK);
    NEAR(read_named_parameter("_plane"), 180);
    CHECK(named_parameter_block("G19") == Status_OK);
    NEAR(read_named_parameter("_plane"), 190);
    CHECK(named_parameter_block("G17") == Status_OK);
    NEAR(read_named_parameter("_plane"), 170);
    return EXIT_SUCCESS;
}
