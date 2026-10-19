#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set some modal state
    char block1[] = "G90G94G17G21G40G49G80G98";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.modal.units_imperial == false);
    CHECK(gc_state.modal.cutter_comp.side == CutterComp_Disable);
    CHECK(gc_state.modal.tool_length_offset == 0.0f);
    CHECK(gc_state.modal.motion == MotionMode_Cancel);
    CHECK(gc_state.modal.canned_return == CannedReturn_RPlane);

    // M70 - Save modal state
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);

    // Change modal state
    char block3[] = "G91G93G18G20G41G43H1G81G99";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Incremental);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(gc_state.modal.units_imperial == true);
    CHECK(gc_state.modal.cutter_comp.side == CutterComp_Left);
    CHECK(gc_state.modal.tool_length_offset != 0.0f);
    CHECK(gc_state.modal.motion == MotionMode_G81);
    CHECK(gc_state.modal.canned_return == CannedReturn_Initial);

    // M72 - Restore modal state
    char block4[] = "M72";
    CHECK(gc_execute_block(block4) == Status_OK);

    // Modal state should be restored
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.modal.units_imperial == false);
    CHECK(gc_state.modal.cutter_comp.side == CutterComp_Disable);
    CHECK(gc_state.modal.tool_length_offset == 0.0f);
    CHECK(gc_state.modal.motion == MotionMode_Cancel);
    CHECK(gc_state.modal.canned_return == CannedReturn_RPlane);

    return EXIT_SUCCESS;
}