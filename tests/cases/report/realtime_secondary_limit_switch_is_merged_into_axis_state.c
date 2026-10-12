#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); realtime_limits.min2.y = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:Y>") != NULL);
    return EXIT_SUCCESS;
}
