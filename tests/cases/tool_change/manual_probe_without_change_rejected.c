#include "support/engine_host.h"
#include "tool_change.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.tool_change.mode = ToolChange_Manual;
    CHECK(tc_probe_workpiece() == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
