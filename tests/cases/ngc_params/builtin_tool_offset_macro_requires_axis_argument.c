#include "support/builtin_macro_host.h"
#include "support/tool_offset_host.h"
#include "check.h"

int main(void)
{
    prepare_offset_tool();
    CHECK(builtin_macro_block("G65P2Q1") == Status_GcodeValueWordMissing);
    NEAR(builtin_macro_result("_value_returned"), 0);
    return EXIT_SUCCESS;
}
