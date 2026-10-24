#include "support/mpg_observer_host.h"
int main(void)
{
    prepare_mpg_stream();
    hal.periph_port.set_pin_description = describe_rx;
    grbl.on_mpg_registered = NULL;
    CHECK(stream_mpg_register(&pendant_device,true,stream_mpg_check_enable));
    CHECK(description_calls == 1 && !pendant_tx_capable);
    CHECK(registered_calls == 0 && hal.stream.read == primary_input);
    return EXIT_SUCCESS;
}
