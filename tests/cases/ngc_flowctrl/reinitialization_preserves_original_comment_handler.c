#include "support/flow_comment_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_comment();
    ngc_flowctrl_init();
    ngc_flowctrl_init();
    char comment[] = "operator note";
    CHECK(grbl.on_gcode_comment(comment) == Status_OK);
    CHECK(prior_comment_calls == 1 && process_comment_calls == 0);
    return EXIT_SUCCESS;
}
