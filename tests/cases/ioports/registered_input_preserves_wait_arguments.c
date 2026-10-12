#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_wait_on_input(Port_Digital, 1, WaitMode_Immediate, 2.5f) == 1);
    CHECK(read_calls == 1);
    CHECK(physical_input == 1);
    CHECK(input_mode == WaitMode_Immediate);
    NEAR(input_timeout, 2.5f);
    return EXIT_SUCCESS;
}
