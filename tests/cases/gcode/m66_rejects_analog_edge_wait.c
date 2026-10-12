#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M66E0L1Q1") == Status_GcodeValueOutOfRange);
    CHECK(analog_read_calls == 0);
    return EXIT_SUCCESS;
}
