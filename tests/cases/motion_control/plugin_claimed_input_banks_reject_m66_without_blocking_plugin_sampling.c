#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M66P0L0") == Status_OK);
    CHECK(read_calls == 1 && physical_input == 0);
    uint8_t digital[2], analog[2];
    claim_fixture_ports(Port_Digital, Port_Input, digital);
    claim_fixture_ports(Port_Analog, Port_Input, analog);
    read_calls = analog_read_calls = 0;
    CHECK(ioports_can_do().wait_on_input);
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G20G91M66P0L0G1X10F1", Status_GcodeUnsupportedCommand);
    CHECK(read_calls == 0 && analog_read_calls == 0);
    CHECK(ioport_wait_on_input(Port_Digital, digital[0], WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && physical_input == 0);
    CHECK(ioport_wait_on_input(Port_Analog, analog[0], WaitMode_Immediate, 0) == 123);
    CHECK(analog_read_calls == 1 && analog_input_port == 0);
    return EXIT_SUCCESS;
}
