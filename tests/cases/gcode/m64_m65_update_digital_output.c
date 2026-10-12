#include "support/io_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M64P1") == Status_OK);
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(io_block("M65P1") == Status_OK);
    CHECK(output_calls == 2 && physical_output == 1 && !output_value);
    return EXIT_SUCCESS;
}
