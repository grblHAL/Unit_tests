#include "support/engine_host.h"
#include "tool_change.h"
#include "report.h"
#include "check.h"
static atc_status_t no_atc(void) { return ATC_None; }
static bool suspend(bool value) { return value; }
int main(void)
{
    engine_prepare();
    hal.tool.atc_get_state = no_atc;
    hal.stream.suspend_read = suspend;
    settings.tool_change.mode = ToolChange_Manual;
    tc_init();
    CHECK(hal.tool.change != NULL);
    CHECK(grbl.on_toolchange_ack != NULL);
    CHECK(hal.stream.report.flags.value & Report_TLOReference);
    return EXIT_SUCCESS;
}
