#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_program_block("M3S5000$1") == Status_GcodeValueOutOfRange);
    CHECK(spindle_output_calls[0] == 0 && spindle_output_calls[1] == 0);
    return EXIT_SUCCESS;
}
