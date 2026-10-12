#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M66P0L1") == Status_GcodeValueOutOfRange);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
