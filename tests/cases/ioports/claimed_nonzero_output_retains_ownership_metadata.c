#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    uint8_t relay = 1;
    CHECK(ioport_claim(Port_Digital, Port_Output, &relay, "Vacuum relay") == &digital_pins[Port_Output][1]);
    bool claimed = hal.port.get_pin_info(Port_Digital, Port_Output, relay)->mode.claimed;
    unsigned available = ioports_unclaimed(Port_Digital, Port_Output);
    CHECK(ioport_digital_out(relay, true));
    CHECK(physical_output == 1 && output_value);
    CHECK(ioport_digital_out(0, false));
    CHECK(physical_output == 0 && !output_value && output_calls == 2);
    uint8_t duplicate = 1;
    CHECK(ioport_claim(Port_Digital, Port_Output, &duplicate, "Other relay") == NULL);
    CHECK(duplicate == IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    fprintf(stderr, "claimed relay metadata=%u, available outputs=%u\n", claimed, available);
    CHECK(claimed && available == 1);
    return EXIT_SUCCESS;
}
