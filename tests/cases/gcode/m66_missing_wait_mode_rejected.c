#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M66P0") == Status_GcodeValueWordMissing);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
