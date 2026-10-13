#include "support/parser_change_report_host.h"

int main(void)
{
    prepare_parser_change_report();
    CHECK(named_parameter_block("G43.1Z4") == Status_OK);
    status_report_tracking_t tracking = {.flags = {.tool_offset = true}};
    system_clear_exec_state_flag(EXEC_TLO_REPORT);
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(sys.rt_exec_state & EXEC_TLO_REPORT);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 4);
    return EXIT_SUCCESS;
}
