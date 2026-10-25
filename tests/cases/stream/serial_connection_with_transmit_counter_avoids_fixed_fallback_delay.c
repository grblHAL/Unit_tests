#include "support/stream_connection_host.h"
static unsigned transmit_checks;
static uint16_t drained_transmit_count(void) { transmit_checks++; return 0; }

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    io_stream_t serial = primary_connection;
    serial.instance = 2;
    serial.get_tx_buffer_count = drained_transmit_count;
    clear_connection_output();
    uint32_t before = engine_ticks;
    CHECK(stream_connect(&serial));
    CHECK(transmit_checks > 0);
    CHECK(engine_ticks == before);
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.is_connected());
    CHECK(strstr(primary_output, "SERIAL STREAM ACTIVE") != NULL);
    clear_connection_output();
    hal.stream.write("status");
    CHECK(strcmp(primary_output, "status") == 0);
    stream_disconnect(&serial);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
