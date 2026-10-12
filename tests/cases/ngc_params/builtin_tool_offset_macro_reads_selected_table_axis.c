#include "support/builtin_macro_host.h"
#include "support/tool_offset_host.h"
#include "check.h"

int main(void)
{
    prepare_offset_tool();
    CHECK(builtin_macro_block("G65P2Q1R2") == Status_OK);
    NEAR(builtin_macro_result("_value"), 4);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(gc_state.tool->tool_id == 0);
    return EXIT_SUCCESS;
}
