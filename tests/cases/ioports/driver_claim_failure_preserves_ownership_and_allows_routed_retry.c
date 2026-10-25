#include "support/ioports_host.h"

static claim_port_ptr original_claim;
static bool reject_claim = true;
static unsigned driver_claim_calls;
static bool claim_with_failure(io_port_type_t type, io_port_direction_t dir,
    uint8_t *port, const char *description)
{
    driver_claim_calls++;
    return reject_claim ? false : original_claim(type, dir, port, description);
}
int main(void)
{
    prepare_ioports();
    original_claim = hal.port.claim;
    CHECK(original_claim != NULL);
    hal.port.claim = claim_with_failure;
    const char *description = digital_pins[Port_Output][0].description;
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    io_port_cfg_t configuration = {0};
    CHECK(ioports_cfg(&configuration, Port_Digital, Port_Output) == &configuration);
    CHECK(configuration.n_ports == 2 && configuration.port_max == 1);
    uint8_t port = 0;
    CHECK(configuration.claim(&configuration, &port, "Vacuum", (pin_cap_t){0}) == NULL);
    CHECK(port == IOPORT_UNASSIGNED && driver_claim_calls == 1);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    CHECK(hal.port.num_digital_out == 2);
    CHECK(!digital_pins[Port_Output][0].mode.claimed);
    CHECK(!digital_pins[Port_Output][1].mode.claimed);
    CHECK(digital_pins[Port_Output][0].description == description);

    reject_claim = false;
    port = 0;
    CHECK(configuration.claim(&configuration, &port, "Vacuum", (pin_cap_t){0}) == &digital_pins[Port_Output][0]);
    CHECK(driver_claim_calls == 2 && port != IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(hal.port.num_digital_out == 1);
    CHECK(digital_pins[Port_Output][0].mode.claimed);
    CHECK(strcmp(digital_pins[Port_Output][0].description, "Vacuum") == 0);
    CHECK(ioport_digital_out(port, true));
    CHECK(output_calls == 1 && physical_output == 0 && output_value);
    return EXIT_SUCCESS;
}
