#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); realtime_probe.triggered = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:P>") != NULL);
    return EXIT_SUCCESS;
}
