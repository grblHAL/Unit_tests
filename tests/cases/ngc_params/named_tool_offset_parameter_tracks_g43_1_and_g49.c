#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G43.1Z5") == Status_OK);
    NEAR(read_named_parameter("_tool_offset"), 1);
    CHECK(named_parameter_block("G49") == Status_OK);
    NEAR(read_named_parameter("_tool_offset"), 0);
    return EXIT_SUCCESS;
}
