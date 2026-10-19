#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    uint8_t plugin = 0;
    CHECK(ioport_claim(Port_Analog, Port_Output, &plugin, "Plugin setpoint") != NULL);
    CHECK(ioports_unclaimed(Port_Analog, Port_Output) == 1);
    CHECK(io_block("M68E0Q12") == Status_OK);
    CHECK(analog_output_calls == 1 && analog_output_port == 1);
    NEAR(analog_output_value, 12);
    CHECK(ioport_analog_out(plugin, 15));
    CHECK(analog_output_calls == 2 && analog_output_port == 0);
    NEAR(analog_output_value, 15);
    /* The ownership contract is rejection without driving the reserved port. */
    CHECK(io_block("M68E1Q9") != Status_OK);
    CHECK(analog_output_calls == 2);
    CHECK(analog_output_port_log[0] == 1 && analog_output_port_log[1] == 0);
    return EXIT_SUCCESS;
}
