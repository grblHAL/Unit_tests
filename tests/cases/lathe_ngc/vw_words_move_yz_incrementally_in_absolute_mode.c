#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    sys.position[X_AXIS] = 800; sys.position[Y_AXIS] = 1600; sys.position[Z_AXIS] = 2400; sync_position();
    CHECK(css_block("G90G1V4W6F100") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 10); NEAR(gc_state.position[Y_AXIS], 24); NEAR(gc_state.position[Z_AXIS], 36);
    CHECK(!gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
