#include "support/lathe_restore_runtime_host.h"
int main(void)
{
    prepare_lathe_restore();
    CHECK(laser_block("G7") == Status_OK);
    CHECK(laser_block("M70") == Status_OK);
    CHECK(laser_block("G8") == Status_OK);
    report_add_realtime(Report_ClearAll);
    CHECK(ngc_modal_state_restore());
    CHECK(gc_state.modal.diameter_mode);
    CHECK((hal.stream.report.flags.value & Report_LatheXMode) != 0);
    CHECK(!laser_output_state.on && plan_get_current_block() == NULL);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
