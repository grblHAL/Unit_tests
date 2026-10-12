#include "support/ioports_host.h"

int main(void)
{
    prepare_ioports();
    aux_ctrl_t input = {.port = 255, .function = Input_FeedHold, .signal = {.feed_hold = true}};
    aux_ctrl_out_t output = {.port = 255, .function = Output_CoolantMist};
    pin_function_t in_function = Input_Aux0, out_function = Output_Aux0;
    hal.signals_cap.feed_hold = false;
    ioport_assign_function(&input, &in_function);
    ioport_assign_out_function(&output, &out_function);
    CHECK(in_function == Input_Aux0 && out_function == Output_Aux0);
    CHECK(!hal.signals_cap.feed_hold);
    return EXIT_SUCCESS;
}
