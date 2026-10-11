#include "support/sync_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_sync_parser();
    spindle_get(0)->get_data = NULL;
    CHECK(css_block("G33Z1K1") == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.position[Z_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
