#include "support/ioports_legacy_host.h"

static xbar_t relay = {.id = 0, .function = Output_Aux0,
    .cap = {.output = true, .claimable = true}};
static unsigned claim_calls, output_calls;
static bool relay_level;
static xbar_t *relay_info(io_port_type_t type, io_port_direction_t dir, uint8_t port)
{
    return type == Port_Digital && dir == Port_Output && port == 0 ? &relay : NULL;
}
static bool claim_relay(io_port_type_t type, io_port_direction_t dir,
    uint8_t *port, const char *description)
{
    CHECK(type == Port_Digital && dir == Port_Output && *port == 0);
    CHECK(hal.port.num_digital_out == 1 && !relay.mode.claimed);
    claim_calls++;
    hal.port.num_digital_out--;
    relay.description = description;
    return true;
}
static void output_relay(uint8_t port, bool on)
{
    CHECK(port == 0);
    output_calls++;
    relay_level = on;
}

int main(void)
{
    prepare_legacy_ports();
    hal.port.get_pin_info = relay_info;
    hal.port.claim = claim_relay;
    hal.port.digital_out = output_relay;
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Digital, 0, 1));
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Relay") == &relay);
    CHECK(claim_calls == 1 && port == 0 && relay.mode.claimed);
    CHECK(hal.port.num_digital_out == 0 && hal.port.num_digital_in == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 0);
    CHECK(ioport_digital_out(port, true) && relay_level && output_calls == 1);
    CHECK(ioport_digital_out(port, false) && !relay_level && output_calls == 2);
    CHECK(strcmp(relay.description, "Relay") == 0);
    return EXIT_SUCCESS;
}
