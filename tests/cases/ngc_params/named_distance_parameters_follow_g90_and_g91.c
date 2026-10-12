#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G91") == Status_OK);
    NEAR(read_named_parameter("_incremental"), 1);
    NEAR(read_named_parameter("_absolute"), 0);
    CHECK(named_parameter_block("G90") == Status_OK);
    NEAR(read_named_parameter("_incremental"), 0);
    NEAR(read_named_parameter("_absolute"), 1);
    return EXIT_SUCCESS;
}
