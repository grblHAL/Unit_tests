#include "support/rtu_host.h"

int main(void)
{
    CHECK(modbus_get_rtu_stream() == NULL);
    prepare_rtu();
    modbus_rtu_stream_t *stream = modbus_get_rtu_stream();
    CHECK(stream != NULL);
    CHECK(stream->read != NULL && stream->write != NULL);
    CHECK(stream->get_rx_buffer_count() == 0);
    return EXIT_SUCCESS;
}
