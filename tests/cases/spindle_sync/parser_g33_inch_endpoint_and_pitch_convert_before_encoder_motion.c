#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    CHECK(sync_parser_block("G20") == Status_OK);
    CHECK(sync_parser_block("G33Z0.1K0.05") == Status_OK);
    NEAR(gc_state.distance_per_rev, 1.27f);
    NEAR(gc_state.position[Z_AXIS], 2.54f);
    CHECK(axis_pulses[Z_AXIS] == 203 && physical_position[Z_AXIS] == 203);
    CHECK(sync_encoder_resets == 1 && !sync_parser_driver_running);
    CHECK(!sys.override.control.feed_rates_disable && !sys.abort);
    return EXIT_SUCCESS;
}
