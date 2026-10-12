#include "support/passthru_host.h"
#include "check.h"
static bool connected(void) { return true; }

int main(void)
{
    prepare_passthru();
    hal.stream.is_connected = connected;
    stream_passthru_init(2, 115200, true);
    CHECK(!hal.stream.state.passthru);
    CHECK(usb_handler == NULL);
    CHECK(strstr(engine_output, "Entering passthru mode failed!") != NULL);
    return EXIT_SUCCESS;
}
