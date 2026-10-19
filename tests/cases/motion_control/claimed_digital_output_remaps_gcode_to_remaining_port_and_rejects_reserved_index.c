#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_io_motion();
    uint8_t plugin = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &plugin, "Plugin relay") != NULL);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(io_block("M64P0") == Status_OK);
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(ioport_digital_out(plugin, 0));
    CHECK(output_calls == 2 && physical_output == 0 && !output_value);
    CHECK(io_block("M65P0") == Status_OK);
    CHECK(output_calls == 3 && physical_output == 1 && !output_value);
    CHECK(io_block("M64P1") == Status_GcodeValueOutOfRange);
    CHECK(output_calls == 3);
    CHECK(output_pin_log[0] == 1 && output_pin_log[1] == 0 && output_pin_log[2] == 1);
    return EXIT_SUCCESS;
}
