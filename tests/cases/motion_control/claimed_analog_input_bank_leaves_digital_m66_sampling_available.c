#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    uint8_t analog[2];
    claim_fixture_ports(Port_Analog, Port_Input, analog);
    CHECK(io_block("M66E0L0") == Status_GcodeValueOutOfRange);
    CHECK(analog_read_calls == 0);
    CHECK(io_block("M66P0L0") == Status_OK);
    CHECK(read_calls == 1 && physical_input == 0);
    CHECK(sys.var5399 == 1);
    CHECK(ioport_wait_on_input(Port_Analog, analog[0], WaitMode_Immediate, 0) == 123);
    CHECK(analog_read_calls == 1 && analog_input_port == 0);
    return EXIT_SUCCESS;
}
