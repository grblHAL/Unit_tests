#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_remap(Port_Digital, Port_Output, 0, 1));
    CHECK(ioport_remap(Port_Digital, Port_Output, 0, 1));
    CHECK(ioport_digital_out(0, 1));
    CHECK(physical_output == 1);
    CHECK(ioport_digital_out(1, 1));
    CHECK(physical_output == 0);
    CHECK(output_calls == 2);
    uint8_t owned = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &owned, "Vacuum relay") == &digital_pins[Port_Output][0]);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(!ioport_remap(Port_Digital, Port_Output, 0, owned));
    CHECK(ioport_digital_out(owned, false));
    CHECK(physical_output == 0 && !output_value);
    CHECK(ioport_digital_out(0, false));
    CHECK(physical_output == 1 && !output_value && output_calls == 4);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    return EXIT_SUCCESS;
}
