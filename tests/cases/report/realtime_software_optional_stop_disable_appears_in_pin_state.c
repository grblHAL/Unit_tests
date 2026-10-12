#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); sys.flags.optional_stop_disable = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:T>") != NULL);
    return EXIT_SUCCESS;
}
