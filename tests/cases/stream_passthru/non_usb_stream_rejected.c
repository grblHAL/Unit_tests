#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    hal.stream.state.is_usb = false;
    stream_passthru_init(1, 115200, true);
    CHECK(!hal.stream.state.passthru);
    CHECK(usb_handler == NULL);
    CHECK(uart_handler == NULL);
    return EXIT_SUCCESS;
}
