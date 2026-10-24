#include "support/ioports_host.h"

int main(void)
{
    engine_prepare();
    static io_ports_data_t ports = {.out.n_ports = 1};
    static io_digital_t relay = {.ports = &ports, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output};
    CHECK(ioports_add_digital(&relay));
    io_port_cfg_t configuration = {0};
    CHECK(ioports_cfg(&configuration, Port_Digital, Port_Output) == &configuration);
    CHECK(configuration.n_ports == 1 && configuration.port_max == 0);
    CHECK(configuration.get_next(&configuration, IOPORT_UNASSIGNED, NULL, (pin_cap_t){0}) == 0);
    CHECK(configuration.get_next(&configuration, 0, NULL, (pin_cap_t){0}) == IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    CHECK(ioport_set_description(Port_Digital, Port_Output, 0, "Vacuum relay"));
    uint8_t selected = configuration.get_next(&configuration, 0, "Vacuum relay", (pin_cap_t){0});
    CHECK(selected == 0);
    CHECK(configuration.claim(&configuration, &selected, "Vacuum relay", (pin_cap_t){0}) == &digital_pins[Port_Output][0]);
    CHECK(digital_pins[Port_Output][0].mode.claimed);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 0);
    uint8_t duplicate = 0;
    CHECK(configuration.claim(&configuration, &duplicate, "Other accessory", (pin_cap_t){0}) == NULL);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 0 && output_calls == 0);
    CHECK(ioport_digital_out(selected, true));
    CHECK(output_calls == 1 && physical_output == 0 && output_value);
    CHECK(ioport_digital_out(selected, false));
    CHECK(output_calls == 2 && physical_output == 0 && !output_value);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 0);
    return EXIT_SUCCESS;
}
