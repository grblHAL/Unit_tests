#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M64P0") == Status_OK);
    CHECK(output_calls == 1 && physical_output == 0 && output_value);
    uint8_t claimed[2];
    claim_fixture_ports(Port_Digital, Port_Output, claimed);
    output_calls = 0;
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G20G91M62P0G1X10F1", Status_GcodeUnsupportedCommand);
    CHECK(output_calls == 0);
    CHECK(ioport_digital_out(claimed[0], 1));
    CHECK(output_calls == 1 && physical_output == 0 && output_value);
    return EXIT_SUCCESS;
}
