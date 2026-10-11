#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.stream.suspend_read = build_suspend;
    settings.tool_change.mode = ToolChange_Ignore;
    build_report(true);
    CHECK(strstr(engine_output, ",TC,") == NULL);
    CHECK(strstr(engine_output, "ATC=") == NULL);
    return EXIT_SUCCESS;
}
