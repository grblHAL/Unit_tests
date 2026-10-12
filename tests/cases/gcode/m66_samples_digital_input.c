#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M66P1L0") == Status_OK);
    CHECK(read_calls == 1);
    CHECK(physical_input == 1);
    CHECK(input_mode == WaitMode_Immediate);
    CHECK(sys.var5399 == 1);
    return EXIT_SUCCESS;
}
