#include "support/engine_host.h"
#include "tool_change.h"
#include "report.h"
#include "check.h"
static atc_status_t online(void) { return ATC_Online; }
static status_code_t existing(parser_state_t *state) { (void)state; return Status_OK; }
int main(void)
{
    engine_prepare();
    hal.tool.atc_get_state = online;
    hal.tool.change = existing;
    settings.tool_change.mode = ToolChange_Manual;
    tc_init();
    CHECK(hal.tool.change == existing);
    return EXIT_SUCCESS;
}
