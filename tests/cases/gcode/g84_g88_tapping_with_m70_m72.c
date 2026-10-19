#include "support/laser_program_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_pwm_program_mode(Mode_Lathe, false);

    // Set initial modal state
    CHECK(laser_block("G90G94G17G21") == Status_OK);

    // M70 - Save modal state
    CHECK(laser_block("M70") == Status_OK);

    // G84 tapping cycle
    CHECK(laser_block("G84X10Z-20R5F1.0") == Status_OK);

    // M72 - Restore modal state
    CHECK(laser_block("M72") == Status_OK);

    // Modal state should be restored
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.modal.units_imperial == false);

    return EXIT_SUCCESS;
}