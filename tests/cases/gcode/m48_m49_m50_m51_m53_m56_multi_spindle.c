#include "support/multi_spindle_modal_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();

    // M48 - Enable feed and speed override (default spindle)
    CHECK(spindle_program_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M51 P0 $1 - Disable spindle 1 override
    CHECK(spindle_program_block("M51P0$1") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 2); // Spindle 1 disabled

    // M51 P50 $0 - Set spindle 0 override to 50%
    CHECK(spindle_program_block("M51P50$0") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 2); // Spindle 1 still disabled

    // M49 - Disable feed and speed override (default spindle)
    CHECK(spindle_program_block("M49") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 3); // Both spindles disabled

    // M48 - Re-enable
    CHECK(spindle_program_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M53 P0 - Disable feed hold override
    CHECK(spindle_program_block("M53P0") == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == Off);

    // M53 P1 - Enable feed hold override
    CHECK(spindle_program_block("M53P1") == Status_OK);
    CHECK(sys.override.control.feed_hold_disable == On);

    return EXIT_SUCCESS;
}