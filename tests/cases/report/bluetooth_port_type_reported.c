#include "support/report_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    static io_stream_properties_t port = {.type = StreamType_Bluetooth, .instance = 2};
    static io_stream_details_t details = {.n_streams = 1, .streams = &port};
    stream_register_streams(&details);
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:2|BT||]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
