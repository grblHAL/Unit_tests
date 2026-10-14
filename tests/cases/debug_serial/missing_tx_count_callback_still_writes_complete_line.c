#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    hal.debug.get_tx_buffer_count = NULL;
    debug_writeln("probe complete");
    CHECK(strcmp(debug_output, "probe complete" ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 0);
    return EXIT_SUCCESS;
}
