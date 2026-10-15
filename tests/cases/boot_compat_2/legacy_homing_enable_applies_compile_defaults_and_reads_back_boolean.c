#include "support/boot_legacy_limits_host.h"

int main(void)
{
    run_legacy_limit_board("$22=1\n$22\n");
    CHECK(settings.homing.flags.enabled);
    CHECK(settings.homing.flags.init_lock == DEFAULT_HOMING_INIT_LOCK);
    CHECK(settings.homing.flags.single_axis_commands == DEFAULT_HOMING_SINGLE_AXIS_COMMANDS);
    CHECK(settings.homing.cycle[0].mask == Z_AXIS_BIT);
    CHECK(settings.homing.cycle[1].mask == (X_AXIS_BIT | Y_AXIS_BIT));
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(settings.axis[axis].homing_feed_rate, 50);
        NEAR(settings.axis[axis].homing_seek_rate, 500);
    }
    CHECK(strstr(engine_output, "$22=1" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
