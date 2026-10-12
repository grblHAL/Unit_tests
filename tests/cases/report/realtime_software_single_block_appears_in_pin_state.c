#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); sys.flags.single_block = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:Q>") != NULL);
    return EXIT_SUCCESS;
}
