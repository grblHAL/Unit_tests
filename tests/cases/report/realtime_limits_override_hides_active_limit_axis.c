#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); realtime_limits.min.x = true; realtime_controls.limits_override = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:X") == NULL);
    return EXIT_SUCCESS;
}
