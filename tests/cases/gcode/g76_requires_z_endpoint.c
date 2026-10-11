#include "support/sync_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_sync_parser();

    CHECK(css_block("G76P1I1J0.1K1") == Status_GcodeValueWordMissing);
    NEAR(gc_state.position[Z_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
