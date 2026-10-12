#include "support/analog_motion_host.h"
#include <math.h>
#include "check.h"

int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M66E1L0") == Status_OK);
    CHECK(analog_read_calls == 1);
    CHECK(analog_input_port == 1);
    CHECK(analog_input_mode == WaitMode_Immediate);
    CHECK(sys.var5399 == 123);
    return EXIT_SUCCESS;
}
