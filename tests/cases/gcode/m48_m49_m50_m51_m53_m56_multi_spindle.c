#include "support/multi_spindle_modal_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);
    CHECK(spindle_program_block("M51P0$1") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 2);
    CHECK(spindle_program_block("M51P50$0") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 2);
    CHECK(spindle_program_block("M49") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 3);
    CHECK(spindle_program_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 2);
    CHECK(spindle_program_block("M53P0") == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);
    CHECK(spindle_program_block("M53P1") == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);

    return EXIT_SUCCESS;
}
