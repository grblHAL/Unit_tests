#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M66P0E0L0") == Status_ValueWordConflict);
    CHECK(analog_read_calls == 0);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
