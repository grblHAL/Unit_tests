#include "support/lathe_cycle_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_lathe_capture();
    /* Plain G71 is pending implementation; see tests/TODO.md. */
    CHECK(css_block("G71X10Z20Q7F100") == Status_GcodeUnusedWords);
    CHECK(lathe_cycle_calls == 0);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
