#include "support/lathe_cycle_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_lathe_capture(); CHECK(css_block("G70X10Z20Q7D2E3P4F100") == Status_OK);
    CHECK(lathe_cycle_calls == 1 && lathe_cycle_label == 7);
    NEAR(lathe_cycle_args.finish.start_distance, 2); NEAR(lathe_cycle_args.finish.end_distance, 3);
    NEAR(lathe_cycle_args.finish.passes, 4);
    return EXIT_SUCCESS;
}
