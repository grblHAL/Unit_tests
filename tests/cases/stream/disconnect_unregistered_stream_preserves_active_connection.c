#include "support/stream_three_host.h"
int main(void)
{
    prepare_three_streams();
    io_stream_t unregistered = third_connection;
    unregistered.instance = 9;
    unsigned changes = connection_changes;
    stream_disconnect(&unregistered);
    CHECK(connection_changes == changes && hal.stream.write == third_write);
    clear_three_outputs();
    hal.stream.write_all("fixture");
    CHECK(strcmp(third_output,"fixture") == 0);
    stream_disconnect(&third_connection);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
