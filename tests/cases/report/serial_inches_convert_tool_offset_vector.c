#include "support/report_host.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    report_init();
    gc_state.modal.tool_length_offset[Z_AXIS] = -25.4f;
    report_tool_offsets();
    CHECK(strcmp(engine_output, "[TLO:0.0000,0.0000,-1.0000]" ASCII_EOL) == 0);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], -25.4f);
    return EXIT_SUCCESS;
}
