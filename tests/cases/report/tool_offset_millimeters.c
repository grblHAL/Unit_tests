#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    gc_state.modal.tool_length_offset[Z_AXIS] = 12.5f;
    report_tool_offsets();
    CHECK(strcmp(engine_output, "[TLO:0.000,0.000,12.500]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
