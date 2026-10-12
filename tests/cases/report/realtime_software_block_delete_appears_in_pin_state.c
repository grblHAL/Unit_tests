#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); sys.flags.block_delete_enabled = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:L>") != NULL);
    return EXIT_SUCCESS;
}
