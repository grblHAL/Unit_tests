#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // Set initial state
    char block1[] = "G90G94G17";
    CHECK(gc_execute_block(block1) == Status_OK);

    // M70 - Save level 1
    char block2[] = "M70";
    CHECK(gc_execute_block(block2) == Status_OK);

    // Change state
    char block3[] = "G91G93G18";
    CHECK(gc_execute_block(block3) == Status_OK);

    // M70 - Save level 2
    char block4[] = "M70";
    CHECK(gc_execute_block(block4) == Status_OK);

    // Change state
    char block5[] = "G90G94G19";
    CHECK(gc_execute_block(block5) == Status_OK);

    // M72 - Restore level 2
    char block6[] = "M72";
    CHECK(gc_execute_block(block6) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Incremental);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);

    // M72 - Restore level 1
    char block7[] = "M72";
    CHECK(gc_execute_block(block7) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMinute);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);

    return EXIT_SUCCESS;
}