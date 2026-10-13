#include "support/report_host.h"

int main(void)
{
    prepare_report();
    gc_state.modal.tool_length_offset[Z_AXIS] = 25.4f;
    report_tool_offsets();
    CHECK(strcmp(engine_output, "[TLO:0.000,0.000,25.400]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    settings.flags.report_inches = true;
    report_init();
    report_tool_offsets();
    CHECK(strcmp(engine_output, "[TLO:0.0000,0.0000,1.0000]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    settings.flags.report_inches = false;
    report_init();
    report_tool_offsets();
    CHECK(strcmp(engine_output, "[TLO:0.000,0.000,25.400]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
