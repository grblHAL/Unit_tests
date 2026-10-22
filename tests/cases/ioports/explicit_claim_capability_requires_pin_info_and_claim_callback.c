#include "support/ioports_host.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_can_claim_explicit());
    claim_port_ptr claim = hal.port.claim;
    get_pin_info_ptr get_info = hal.port.get_pin_info;
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    hal.port.claim = NULL;
    CHECK(!ioport_can_claim_explicit());
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "relay") == NULL);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(hal.port.num_digital_out == 2);

    hal.port.claim = claim;
    hal.port.get_pin_info = NULL;
    CHECK(!ioport_can_claim_explicit());
    port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "relay") == NULL);
    CHECK(port == IOPORT_UNASSIGNED);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(!digital_pins[Port_Output][1].mode.claimed);
    CHECK(hal.port.num_digital_out == 2);

    hal.port.get_pin_info = get_info;
    CHECK(ioport_can_claim_explicit());
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "relay") == &digital_pins[Port_Output][0]);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(digital_pins[Port_Output][0].mode.claimed);
    CHECK(strcmp(digital_pins[Port_Output][0].description, "relay") == 0);
    return EXIT_SUCCESS;
}
