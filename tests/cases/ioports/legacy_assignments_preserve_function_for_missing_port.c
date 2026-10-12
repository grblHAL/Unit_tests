#include "support/ioports_host.h"

static unsigned missing_queries;
static xbar_t *missing_pin(io_port_type_t type, io_port_direction_t direction, uint8_t port)
{
    CHECK(type == Port_Digital && port == 0);
    CHECK(direction == Port_Input || direction == Port_Output);
    missing_queries++;
    return NULL;
}

int main(void)
{
    prepare_ioports();
    hal.port.get_pin_info = missing_pin;
    aux_ctrl_t input = {.port = 0, .function = Input_FeedHold, .signal = {.feed_hold = true}};
    aux_ctrl_out_t output = {.port = 0, .function = Output_CoolantMist};
    pin_function_t in_function = Input_Aux0, out_function = Output_Aux0;
    hal.signals_cap.feed_hold = false;
    ioport_assign_function(&input, &in_function);
    ioport_assign_out_function(&output, &out_function);
    CHECK(in_function == Input_Aux0 && out_function == Output_Aux0);
    CHECK(!hal.signals_cap.feed_hold);
    CHECK(missing_queries == 2);
    return EXIT_SUCCESS;
}
