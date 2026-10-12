#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    status_code_t status = io_block("M66P256L0");
    fprintf(stderr, "Status=%u input reads=%u physical port=%u\n", (unsigned)status, read_calls, (unsigned)physical_input);
    CHECK(status == Status_GcodeValueOutOfRange);
    CHECK(read_calls == 0);
    return EXIT_SUCCESS;
}
