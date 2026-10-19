#include "support/flow_host.h"
#include "support/report_host.h"

int main(void)
{
    prepare_report();
    ngc_flowctrl_init();
    settings.flags.ngc_debug_out = true;
    engine_output[0] = '\0';
    char invalid[] = "O10ENDWHILE";
    CHECK(gc_execute_block(invalid) == Status_FlowControlNotExecutingMacro);
    CHECK(strstr(engine_output, "ENDWHILE") != NULL);
    char recovery[] = "G21G90";
    CHECK(gc_execute_block(recovery) == Status_OK);
    CHECK(hal.stream.file == NULL);
    return EXIT_SUCCESS;
}
