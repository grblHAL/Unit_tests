#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); realtime_probe.connected = false;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:O>") != NULL);
    return EXIT_SUCCESS;
}
