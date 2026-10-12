#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"
static uint16_t rx_free(void) { return 73; }

int main(void)
{
    prepare_report();
    settings.status_report.buffer_state = true;
    hal.stream.get_rx_buffer_free = rx_free;
    realtime_report();
    CHECK(strcmp(engine_output, "<Check|WPos:0.000,0.000,0.000|Bf:16,73>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
