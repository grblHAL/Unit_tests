#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G55") == Status_OK);
    NEAR(read_named_parameter("_coord_system"), 550);
    CHECK(named_parameter_block("G59.3") == Status_OK);
    NEAR(read_named_parameter("_coord_system"), 593);
    CHECK(named_parameter_block("G54") == Status_OK);
    NEAR(read_named_parameter("_coord_system"), 540);
    return EXIT_SUCCESS;
}
