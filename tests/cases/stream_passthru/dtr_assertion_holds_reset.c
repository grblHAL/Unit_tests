#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    start_passthru();
    finish_passthru_startup();
    io_stream_properties_t usb = {.flags = {.is_usb = true}};
    hal.stream.on_linestate_changed(&usb, (serial_linestate_t){.dtr = true});
    CHECK(!pin_values[0]);
    CHECK(!pin_values[1]);
    hal.stream.on_linestate_changed(&usb, (serial_linestate_t){.dtr = true, .rts = true});
    CHECK(!pin_values[0]);
    CHECK(pin_values[1]);
    return EXIT_SUCCESS;
}
