#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M68") == Status_GcodeValueWordMissing);
    CHECK(analog_output_calls == 0);
    return EXIT_SUCCESS;
}
