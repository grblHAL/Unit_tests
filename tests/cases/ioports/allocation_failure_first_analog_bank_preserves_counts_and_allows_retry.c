#include "support/multi_bank_ioports_host.h"
#include "support/tracked_malloc_host.h"

int main(void)
{
    prepare_ioports();
    bank_analog_data[0] = (io_ports_data_t){.external = true, .in.n_ports = 1, .out.n_ports = 1};
    bank_analog_pins[0][Port_Input][0] = (xbar_t){.function = Input_Analog_Aux0, .cap.input = true, .cap.analog = true};
    bank_analog_pins[0][Port_Output][0] = (xbar_t){.function = Output_Analog_Aux0, .cap.output = true, .cap.analog = true};
    io_analog_t expansion = {.ports = &bank_analog_data[0], .get_pin_info = analog_info_0,
        .set_pin_description = analog_descr_0, .wait_on_input = analog_wait_0, .analog_out = analog_out_0};
    allocation_heap_reject = 1;
    observe_allocation_heap = true;
    bool added = ioports_add_analog(&expansion);
    observe_allocation_heap = false;
    CHECK(allocation_heap_calls == 1 && allocation_heap_failures == 1);
    CHECK(ioport_wait_on_input(Port_Digital, 0, WaitMode_Immediate, 0) == 1);
    CHECK(read_calls == 1 && bank_input_calls == 0 && bank_output_calls == 0);
    fprintf(stderr, "Failed analog registration returned=%u inputs=%u outputs=%u\n",
        added, hal.port.num_analog_in, hal.port.num_analog_out);
    CHECK(!added);
    CHECK(hal.port.num_analog_in == 0 && hal.port.num_analog_out == 0);
    CHECK(ioports_add_analog(&expansion));
    CHECK(hal.port.num_analog_in == 1 && hal.port.num_analog_out == 1);
    CHECK(ioport_wait_on_input(Port_Analog, 0, WaitMode_Immediate, 0) == 100);
    CHECK(ioport_analog_out(0, 25));
    CHECK(bank_output_calls == 1 && last_bank == 0 && last_local_port == 0);
    return EXIT_SUCCESS;
}
