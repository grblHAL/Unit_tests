#include "support/flow_named_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_named_macro();
    CHECK(flow_command(NGC_MAX_PARAM_ID + 1, "CALL[12]") == Status_FlowControlSyntaxError);
    CHECK(hal.stream.file == NULL);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
