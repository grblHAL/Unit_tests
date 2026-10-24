#include "support/multi_bank_ioports_host.h"
#include "support/ioports_legacy_host.h"
static xbar_t *legacy_pin(io_port_type_t type, io_port_direction_t dir, uint8_t port)
{
    uint8_t count = dir == Port_Input ? hal.port.num_digital_in : hal.port.num_digital_out;
    return type == Port_Digital && port < count ? pin_info(dir, port) : NULL;
}
static int32_t legacy_read(io_port_type_t type, uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(type == Port_Digital);
    return pin_read(port, mode, timeout);
}
int main(void)
{
    prepare_legacy_ports();
    hal.port.get_pin_info = legacy_pin;
    hal.port.digital_out = pin_output;
    hal.port.wait_on_input = legacy_read;
    io_ports_data_t original = {0};
    CHECK(ioports_add(&original, Port_Digital, 1, 1));
    hal.port.digital_out(0, true);
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == 1);

    bank_digital_data[1] = (io_ports_data_t){.external = true, .in.n_ports = 1, .out.n_ports = 1};
    bank_digital_pins[1][Port_Input][0] = (xbar_t){.function = Input_Aux1, .cap.input = true};
    bank_digital_pins[1][Port_Output][0] = (xbar_t){.function = Output_Aux1, .cap.output = true};
    io_digital_t digital = {.ports = &bank_digital_data[1], .get_pin_info = digital_info_1,
        .set_pin_description = digital_descr_1, .wait_on_input = digital_wait_1,
        .digital_out = digital_out_1, .register_interrupt_handler = digital_irq_1};
    bank_analog_data[0] = (io_ports_data_t){.external = true, .in.n_ports = 1, .out.n_ports = 1};
    bank_analog_pins[0][Port_Input][0] = (xbar_t){.function = Input_Analog_Aux0, .cap.input = true, .cap.analog = true};
    bank_analog_pins[0][Port_Output][0] = (xbar_t){.function = Output_Analog_Aux0, .cap.output = true, .cap.analog = true};
    io_analog_t analog = {.ports = &bank_analog_data[0], .get_pin_info = analog_info_0,
        .set_pin_description = analog_descr_0, .wait_on_input = analog_wait_0, .analog_out = analog_out_0};
    CHECK(!ioports_add_digital(&digital));
    CHECK(!ioports_add_analog(&analog));
    CHECK(hal.port.get_pin_info == legacy_pin && hal.port.digital_out == pin_output);
    CHECK(hal.port.wait_on_input == legacy_read && hal.port.set_pin_description == legacy_description);
    CHECK(hal.port.num_digital_in == 1 && hal.port.num_digital_out == 1);
    CHECK(hal.port.num_analog_in == 0 && hal.port.num_analog_out == 0);
    CHECK(bank_input_calls == 0 && bank_output_calls == 0 && bank_irq_calls == 0);
    CHECK(output_calls == 1 && read_calls == 1 && output_value);
    CHECK(ioport_get_info(Port_Digital, Port_Output, 0) == &digital_pins[Port_Output][0]);
    CHECK(ioport_get_info(Port_Analog, Port_Output, 0) == NULL);

    hal.port.digital_out(0, false);
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == 1);
    CHECK(output_calls == 2 && physical_output == 0 && !output_value);
    CHECK(read_calls == 2 && physical_input == 0);
    CHECK(ioports_available(Port_Digital, Port_Output) == 1);
    CHECK(ioports_available(Port_Analog, Port_Output) == 0);
    return EXIT_SUCCESS;
}
