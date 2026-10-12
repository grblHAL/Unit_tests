#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change(); start_manual_change(); engine_output[0]=0; report_gcode_modes(hal.stream.write);
    CHECK(gc_state.tool_change); CHECK(strstr(engine_output," M6 ")!=NULL);
    return EXIT_SUCCESS;
}
