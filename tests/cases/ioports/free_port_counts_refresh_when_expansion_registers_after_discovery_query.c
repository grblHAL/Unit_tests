#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_ioports();
    CHECK(ioports_available(Port_Digital, Port_Input) == 2);
    CHECK(ioports_available(Port_Digital, Port_Output) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    bank_digital_data[1] = (io_ports_data_t){.external = true, .in.n_ports = 2, .out.n_ports = 2};
    for(unsigned dir = 0; dir < 2; dir++) for(unsigned port = 0; port < 2; port++) {
        xbar_t *pin = &bank_digital_pins[1][dir][port];
        pin->id = port;
        pin->function = (pin_function_t)((dir == Port_Input ? Input_Aux0 : Output_Aux0) + 2 + port);
        pin->cap.input = pin->mode.input = dir == Port_Input;
        pin->cap.output = pin->mode.output = dir == Port_Output;
    }
    io_digital_t expansion = {.ports = &bank_digital_data[1],
        .get_pin_info = digital_info_1, .set_pin_description = digital_descr_1,
        .digital_out = digital_out_1, .wait_on_input = digital_wait_1,
        .register_interrupt_handler = digital_irq_1};
    CHECK(ioports_add_digital(&expansion));
    CHECK(ioports_available(Port_Digital, Port_Input) == 4);
    CHECK(ioports_available(Port_Digital, Port_Output) == 4);
    unsigned inputs = ioports_unclaimed(Port_Digital, Port_Input);
    unsigned outputs = ioports_unclaimed(Port_Digital, Port_Output);
    ioport_digital_out(0, false);
    CHECK(output_calls == 1 && physical_output == 0 && !output_value);
    ioport_digital_out(2, true);
    CHECK(bank_output_calls == 1 && last_bank == 1 && last_local_port == 0);
    NEAR(bank_output_value, 1);
    CHECK(ioports_available(Port_Digital, Port_Input) == 4);
    CHECK(ioports_available(Port_Digital, Port_Output) == 4);
    fprintf(stderr, "Free digital ports after expansion: inputs=%u outputs=%u expected=4 each\n", inputs, outputs);
    CHECK(inputs == 4 && outputs == 4);
    return EXIT_SUCCESS;
}
