#include "support/report_host.h"
#include "support/malloc_failure_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    static io_stream_properties_t ports[] = {
        {.type = StreamType_Serial, .instance = 3},
        {.type = StreamType_Telnet, .instance = 2},
        {.type = StreamType_Serial, .instance = 1}
    };
    static io_stream_details_t details = {.n_streams = 3, .streams = ports};
    stream_register_streams(&details);
    fail_malloc = true;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1);
    CHECK(strcmp(engine_output, "[PORT:3|UART||]" ASCII_EOL "[PORT:1|UART||]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
