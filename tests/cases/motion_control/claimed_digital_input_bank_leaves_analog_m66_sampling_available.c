#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    uint8_t digital[2];
    claim_fixture_ports(Port_Digital, Port_Input, digital);
    CHECK(io_block("M66P0L0") == Status_GcodeValueOutOfRange);
    CHECK(read_calls == 0);
    CHECK(io_block("M66E0L0") == Status_OK);
    CHECK(analog_read_calls == 1 && analog_input_port == 0);
    CHECK(sys.var5399 == 123);
    CHECK(ioport_wait_on_input(Port_Digital, digital[0], WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && physical_input == 0);
    return EXIT_SUCCESS;
}
