#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
static uint8_t port_seen;
static bool value_seen;
static void output(uint8_t port, bool value) { port_seen = port; value_seen = value; }
int main(void)
{
    engine_prepare();
    hal.port.digital_out = output;
    CHECK(ioport_digital_out(2, 100));
    CHECK(port_seen == 2 && value_seen);
    CHECK(ioport_digital_out(3, 0));
    CHECK(port_seen == 3 && !value_seen);
    return EXIT_SUCCESS;
}
