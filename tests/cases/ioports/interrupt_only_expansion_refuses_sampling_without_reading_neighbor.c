#include "support/multi_bank_ioports_host.h"

int main(void)
{
    prepare_ioports();
    bank_digital_data[1] = (io_ports_data_t){.external = true, .in.n_ports = 1};
    bank_digital_pins[1][Port_Input][0] = (xbar_t){.function = Input_Aux2,
        .cap.input = true, .mode.input = true};
    io_digital_t interrupts = {.ports = &bank_digital_data[1], .get_pin_info = digital_info_1,
        .set_pin_description = digital_descr_1, .register_interrupt_handler = digital_irq_1};
    CHECK(ioports_add_digital(&interrupts));
    CHECK(ioport_remap(Port_Digital, Port_Input, 0, 2));
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == -1);
    CHECK(bank_input_calls == 0 && read_calls == 0);
    CHECK(ioport_enable_irq(0, IRQ_Mode_Rising, bank_consumer_irq));
    CHECK(bank_irq_calls == 1 && last_bank == 1 && last_local_port == 0 && bank_irq_user_port == 0);
    bank_irq_callback(bank_irq_user_port, true);
    CHECK(bank_received_irq_calls == 1 && bank_received_irq_port == 0 && bank_received_irq_state);
    CHECK(ioport_wait_on_input(Port_Digital, 2, WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && physical_input == 0 && bank_input_calls == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 3 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
