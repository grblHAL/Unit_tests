#include "support/report_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    static io_stream_properties_t ports[] = {
        {.type = StreamType_Serial, .instance = 3},
        {.type = StreamType_Serial, .instance = 1}
    };
    static io_stream_details_t details = {.n_streams = 2, .streams = ports};
    stream_register_streams(&details);
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|UART||]" ASCII_EOL "[PORT:3|UART||]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
