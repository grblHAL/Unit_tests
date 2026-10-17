#include "support/lathe_restore_runtime_host.h"
int main(void)
{
    prepare_lathe_restore();
    CHECK(laser_block("G7") == Status_OK);
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block("G8") == Status_OK);
    CHECK(ngc_modal_state_restore());
    CHECK(gc_state.modal.diameter_mode);
    report_add_realtime(Report_ClearAll);
    CHECK(ngc_modal_state_restore());
    CHECK((hal.stream.report.flags.value & Report_LatheXMode) == 0);
    CHECK(gc_state.modal.diameter_mode && !laser_output_state.on);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
