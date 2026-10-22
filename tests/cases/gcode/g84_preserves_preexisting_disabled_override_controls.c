#include "support/canned_spindle_host.h"

int main(void)
{
    prepare_canned_spindle();
    CHECK(canned_block("M3S1000") == Status_OK);
    CHECK(canned_block("M49") == Status_OK);
    CHECK(canned_block("M53P0") == Status_OK);
    CHECK(sys.override.control.feed_hold_disable);
    CHECK(sys.override.control.feed_rates_disable);
    CHECK(spindle_get(0)->param->option.override_disable);
    execute_canned("G84Z-1R0P0F100");
    CHECK(axis_pulses[Z_AXIS] == 160 && physical_position[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.override.control.feed_hold_disable);
    CHECK(sys.override.control.feed_rates_disable);
    CHECK(gc_state.modal.override_ctrl.feed_hold_disable);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(spindle_get(0)->param->option.override_disable);
    CHECK(gc_state.modal.override_ctrl.spindle_rpm_disable == 1);
    CHECK(canned_spindle_log[canned_spindle_events - 1].state.on);
    CHECK(!canned_spindle_log[canned_spindle_events - 1].state.ccw);
    NEAR(canned_spindle_log[canned_spindle_events - 1].rpm, 1000);
    CHECK(canned_block("G80M48") == Status_OK);
    CHECK(canned_block("M53P1") == Status_OK);
    CHECK(!sys.override.control.feed_hold_disable);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!spindle_get(0)->param->option.override_disable);
    return EXIT_SUCCESS;
}
