#include "support/ioports_cfg_host.h"

int main(void)
{
    engine_prepare();
    static io_ports_data_t input_data = {.in.n_ports = 2};
    static io_digital_t inputs = {.ports = &input_data, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .wait_on_input = pin_read};
    CHECK(ioports_add_digital(&inputs));
    CHECK(ioports_available(Port_Digital, Port_Input) == 2);
    CHECK(ioports_cfg(&port_configuration, Port_Digital, Port_Output) == &port_configuration);
    CHECK(port_configuration.n_ports == 0 && port_configuration.handle == NULL);
    CHECK(port_configuration.get_next == NULL && port_configuration.claim == NULL);
    uint8_t unavailable = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &unavailable, "Expansion relay") == NULL);
    CHECK(unavailable == IOPORT_UNASSIGNED);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2 && output_calls == 0);

    static io_ports_data_t output_data = {.out.n_ports = 2};
    static io_digital_t outputs = {.ports = &output_data, .get_pin_info = pin_info,
        .set_pin_description = pin_description, .digital_out = pin_output};
    CHECK(ioports_add_digital(&outputs));
    CHECK(ioports_cfg(&port_configuration, Port_Digital, Port_Output) == &port_configuration);
    CHECK(port_configuration.n_ports == 2 && port_configuration.port_max == 1);
    uint8_t selected = port_configuration.get_next(&port_configuration, IOPORT_UNASSIGNED,
        NULL, (pin_cap_t){0});
    CHECK(selected == 1);
    CHECK(port_configuration.claim(&port_configuration, &selected, "Expansion relay",
        (pin_cap_t){0}) == &digital_pins[Port_Output][1]);
    CHECK(ioport_digital_out(selected, true));
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(ioport_digital_out(selected, false));
    CHECK(output_calls == 2 && physical_output == 1 && !output_value);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 1);
    return EXIT_SUCCESS;
}
