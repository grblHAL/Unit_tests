#include "support/ioports_cfg_host.h"
int main(void)
{
    engine_prepare();
    static io_ports_data_t data = {.out.n_ports = 1};
    static io_digital_t digital = {.ports = &data, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output};
    CHECK(ioports_add_digital(&digital));
    CHECK(ioports_cfg(&port_configuration, Port_Digital, Port_Output) == &port_configuration);
    CHECK(port_configuration.n_ports == 1 && port_configuration.port_max == 0);
    uint8_t selected = port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED,
        NULL, (pin_cap_t){0});
    CHECK(selected == 0);
    CHECK(port_configuration.get_next(&port_configuration, selected, NULL,
        (pin_cap_t){0}) == IOPORT_UNASSIGNED);
    xbar_t *pin = port_configuration.claim(&port_configuration, &selected,
        "Dust extraction", (pin_cap_t){0});
    CHECK(pin == &digital_pins[Port_Output][0] && pin->mode.claimed);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 0);
    CHECK(port_configuration.get_next(&port_configuration, selected, NULL,
        (pin_cap_t){0}) == IOPORT_UNASSIGNED);
    CHECK(ioport_digital_out(selected, true));
    CHECK(physical_output == 0 && output_value && output_calls == 1);
    CHECK(ioport_digital_out(selected, false));
    CHECK(physical_output == 0 && !output_value && output_calls == 2);
    CHECK(strcmp(pin->description, "Dust extraction") == 0);
    return EXIT_SUCCESS;
}
