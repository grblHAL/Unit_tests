#include "support/multi_bank_ioports_host.h"

int main(void)
{
    prepare_ioports();
    bank_digital_data[1] = (io_ports_data_t){.external = true, .in.n_ports = 1};
    bank_digital_pins[1][Port_Input][0] = (xbar_t){.function = Input_Aux2,
        .cap.input = true, .mode.input = true};
    io_digital_t polling = {.ports = &bank_digital_data[1], .get_pin_info = digital_info_1,
        .set_pin_description = digital_descr_1, .wait_on_input = digital_wait_1};
    CHECK(ioports_add_digital(&polling));
    CHECK(hal.port.num_digital_in == 3 && ioports_unclaimed(Port_Digital, Port_Input) == 3);
    CHECK(ioport_remap(Port_Digital, Port_Input, 0, 2));
    CHECK(!ioport_enable_irq(0, IRQ_Mode_Change, bank_consumer_irq));
    CHECK(irq_calls == 0 && bank_irq_calls == 0 && bank_received_irq_calls == 0);
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == 20);
    CHECK(bank_input_calls == 1 && last_bank == 1 && last_local_port == 0);
    CHECK(ioport_enable_irq(2, IRQ_Mode_Rising, bank_consumer_irq));
    CHECK(irq_calls == 1 && irq_physical_port == 0 && irq_user_port == 2);
    irq_callback(irq_user_port, true);
    CHECK(bank_received_irq_calls == 1 && bank_received_irq_port == 2 && bank_received_irq_state);
    CHECK(ioport_wait_on_input(Port_Digital, 2, WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && physical_input == 0 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
