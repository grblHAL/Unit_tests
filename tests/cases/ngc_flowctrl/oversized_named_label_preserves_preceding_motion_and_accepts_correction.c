#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"
#include "ngc_flowctrl.h"

int main(void)
{
    char rejected[NGC_MAX_PARAM_LENGTH + 12] = "O<";
    memset(rejected + 2, 'A', NGC_MAX_PARAM_LENGTH + 1);
    strcpy(rejected + NGC_MAX_PARAM_LENGTH + 3, ">IF[1]");
    reject_without_losing_queued_motion(rejected, Status_FlowControlSyntaxError);
    char begin[] = "O<guard>IF[1]", assign[] = "#100=11", end[] = "O<guard>ENDIF";
    CHECK(gc_execute_block(begin) == Status_OK);
    CHECK(gc_execute_block(assign) == Status_OK);
    CHECK(gc_execute_block(end) == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 11);
    CHECK(!gc_state.skip_blocks && plan_get_current_block() == NULL);
    ngc_flowctrl_init();
    return EXIT_SUCCESS;
}
