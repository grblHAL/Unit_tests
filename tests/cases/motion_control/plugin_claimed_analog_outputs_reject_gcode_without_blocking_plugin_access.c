#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M68E0Q12") == Status_OK);
    CHECK(analog_output_calls == 1 && analog_output_port == 0);
    NEAR(analog_output_value, 12);
    uint8_t claimed[2];
    claim_fixture_ports(Port_Analog, Port_Output, claimed);
    analog_output_calls = 0;
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G20G91M68E0Q15G1X10F1", Status_GcodeUnsupportedCommand);
    CHECK(analog_output_calls == 0);
    CHECK(ioport_analog_out(claimed[0], 15));
    CHECK(analog_output_calls == 1 && analog_output_port == 0);
    NEAR(analog_output_value, 15);
    return EXIT_SUCCESS;
}
