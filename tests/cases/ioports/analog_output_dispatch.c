#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
static uint8_t port_seen;
static float value_seen;
static bool output(uint8_t port, float value) { port_seen = port; value_seen = value; return true; }
int main(void)
{
    engine_prepare();
    hal.port.analog_out = output;
    CHECK(ioport_analog_out(2, 1.25f));
    CHECK(port_seen == 2);
    NEAR(value_seen, 1.25f);
    return EXIT_SUCCESS;
}
