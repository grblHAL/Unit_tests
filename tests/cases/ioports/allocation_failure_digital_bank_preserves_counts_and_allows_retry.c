#include "support/multi_bank_ioports_host.h"
#include "support/tracked_malloc_host.h"

int main(void)
{
    prepare_ioports();
    bank_digital_data[1] = (io_ports_data_t){.external = true, .in.n_ports = 1, .out.n_ports = 1};
    bank_digital_pins[1][Port_Input][0] = (xbar_t){.function = Input_Aux2, .cap.input = true};
    bank_digital_pins[1][Port_Output][0] = (xbar_t){.function = Output_Aux2, .cap.output = true};
    io_digital_t expansion = {.ports = &bank_digital_data[1], .get_pin_info = digital_info_1,
        .set_pin_description = digital_descr_1, .wait_on_input = digital_wait_1,
        .digital_out = digital_out_1, .register_interrupt_handler = digital_irq_1};
    allocation_heap_reject = 1;
    observe_allocation_heap = true;
    bool added = ioports_add_digital(&expansion);
    observe_allocation_heap = false;
    CHECK(allocation_heap_calls == 1 && allocation_heap_failures == 1);
    hal.port.digital_out(0, true);
    CHECK(output_calls == 1 && physical_output == 0 && output_value && bank_output_calls == 0);
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == 1);
    fprintf(stderr, "Failed digital registration returned=%u inputs=%u outputs=%u\n",
        added, hal.port.num_digital_in, hal.port.num_digital_out);
    CHECK(!added);
    CHECK(hal.port.num_digital_in == 2 && hal.port.num_digital_out == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2 && ioports_unclaimed(Port_Digital, Port_Output) == 2);
    CHECK(ioports_add_digital(&expansion));
    CHECK(hal.port.num_digital_in == 3 && hal.port.num_digital_out == 3);
    CHECK(ioport_wait_on_input(Port_Digital, 2, WaitMode_Immediate, 0) == 20);
    hal.port.digital_out(2, true);
    CHECK(bank_output_calls == 1 && last_bank == 1 && last_local_port == 0);
    return EXIT_SUCCESS;
}
