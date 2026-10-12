#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins();
    sys.flags.block_delete_enabled = sys.flags.optional_stop_disable = sys.flags.single_block = true;
    hal.signals_cap.block_delete = hal.signals_cap.stop_disable = hal.signals_cap.single_block = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:") == NULL);
    return EXIT_SUCCESS;
}
