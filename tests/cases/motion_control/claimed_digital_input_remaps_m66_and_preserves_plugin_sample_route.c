#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_io_motion();
    uint8_t plugin = 0;
    CHECK(ioport_claim(Port_Digital, Port_Input, &plugin, "Plugin switch") != NULL);
    CHECK(io_block("M66P0L0") == Status_OK);
    CHECK(read_calls == 1 && physical_input == 1);
    CHECK(ioport_wait_on_input(Port_Digital, plugin, WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 2 && physical_input == 0);
    CHECK(io_block("M66P1L0") == Status_GcodeValueOutOfRange);
    CHECK(read_calls == 2);
    return EXIT_SUCCESS;
}
