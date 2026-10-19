#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G90G94G17G21G49G80G98") == Status_OK);
    CHECK(incoming_block("M70") == Status_OK);
    CHECK(incoming_block("G91G93G18G20G99") == Status_OK);
    CHECK(incoming_block("M72") == Status_OK);
    CHECK(!gc_state.modal.distance_incremental && !gc_state.modal.units_imperial);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin && gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.modal.retract_mode == CCRetractMode_Previous);
    CHECK(gc_state.modal.motion == MotionMode_None);
    return EXIT_SUCCESS;
}
