#include "support/laser_program_host.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_laser_program(false);

    // Set up overrides
    sys.override.feed_rate = 50;
    sys.override.rapid_rate = 50;
    spindle_set_override(spindle_get(0), 75);
    CHECK(sys.override.feed_rate == 50);
    CHECK(spindle_get(0)->param->state.override_percentage == 75);

    // Start a move
    CHECK(laser_block("G1X10F100") == Status_OK);

    // Simulate feed hold (M0)
    CHECK(laser_block("M0") == Status_OK);
    CHECK(state_get() == STATE_HOLD);

    // Overrides should be preserved during hold
    CHECK(sys.override.feed_rate == 50);
    CHECK(spindle_get(0)->param->state.override_percentage == 75);

    // Resume by clearing hold and continuing
    sys.flags.hold = false;
    state_set(STATE_CYCLE);

    // Overrides should still be preserved
    CHECK(sys.override.feed_rate == 50);
    CHECK(spindle_get(0)->param->state.override_percentage == 75);

    return EXIT_SUCCESS;
}