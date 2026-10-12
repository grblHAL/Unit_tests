#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true); sys.position[X_AXIS] = 1600; sync_position();
    CHECK(css_block("G7G90G1U10F100") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 25); CHECK(gc_state.modal.diameter_mode);
    return EXIT_SUCCESS;
}
