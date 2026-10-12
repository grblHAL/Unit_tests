#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G98") == Status_OK);
    NEAR(read_named_parameter("_retract_r_plane"), 1);
    NEAR(read_named_parameter("_retract_old_z"), 0);
    CHECK(named_parameter_block("G99") == Status_OK);
    NEAR(read_named_parameter("_retract_r_plane"), 0);
    NEAR(read_named_parameter("_retract_old_z"), 1);
    return EXIT_SUCCESS;
}
