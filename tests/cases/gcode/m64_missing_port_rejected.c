#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M64") == Status_GcodeValueWordMissing);
    CHECK(output_calls == 0);
    return EXIT_SUCCESS;
}
