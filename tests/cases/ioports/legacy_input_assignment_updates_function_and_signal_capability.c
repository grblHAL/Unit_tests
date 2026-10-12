#include "support/ioports_host.h"

int main(void)
{
    prepare_ioports();
    aux_ctrl_t control = {.port = 0, .function = Input_FeedHold, .signal = {.feed_hold = true}};
    pin_function_t function = Input_Aux0;
    hal.signals_cap.feed_hold = false;
    ioport_assign_function(&control, &function);
    CHECK(function == Input_FeedHold);
    CHECK(hal.signals_cap.feed_hold);
    return EXIT_SUCCESS;
}
