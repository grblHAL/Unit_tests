#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    uint8_t plugin = 0;
    CHECK(ioport_claim(Port_Analog, Port_Input, &plugin, "Plugin ADC") != NULL);
    CHECK(io_block("M66E0L0") == Status_OK);
    CHECK(analog_read_calls == 1 && analog_input_port == 1);
    CHECK(ioport_wait_on_input(Port_Analog, plugin, WaitMode_Immediate, 0) == 123);
    CHECK(analog_read_calls == 2 && analog_input_port == 0);
    CHECK(io_block("M66E1L0") == Status_GcodeValueOutOfRange);
    CHECK(analog_read_calls == 2);
    return EXIT_SUCCESS;
}
