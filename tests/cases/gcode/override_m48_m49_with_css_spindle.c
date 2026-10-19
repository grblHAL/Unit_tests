#include "support/laser_program_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // Enable CSS mode with M3 S100 D5000
    CHECK(laser_block("G18G96M3S100D5000") == Status_OK);
    CHECK(spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);

    // M48 - Enable feed and speed override
    CHECK(laser_block("M48") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    // M49 - Disable feed and speed override
    CHECK(laser_block("M49") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == On);
    CHECK(sys.override.control.spindle_rpm_disable == 1);

    // M50 P50 - Set feed override to 50%
    CHECK(laser_block("M50P50") == Status_OK);
    CHECK(sys.override.control.feed_rates_disable == Off);

    // M51 P75 - Set spindle override to 75%
    CHECK(laser_block("M51P75") == Status_OK);
    CHECK(sys.override.control.spindle_rpm_disable == 0);

    return EXIT_SUCCESS;
}