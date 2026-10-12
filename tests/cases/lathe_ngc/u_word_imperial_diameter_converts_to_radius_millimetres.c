#include "support/css_host.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true); sys.position[X_AXIS] = 2032; sync_position();
    CHECK(css_block("G20G90G1U1F10") == Status_OK);
    NEAR(gc_state.position[X_AXIS], 38.1f); CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
