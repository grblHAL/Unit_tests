#include "support/stream_connection_host.h"
int main(void)
{
    prepare_report();
    grbl.on_stream_changed = stream_changed;
    const io_stream_t *fallback = stream_null_init(115200);
    CHECK(stream_connect(fallback));
    CHECK(stream_get_base() == fallback && hal.stream.type == StreamType_Null);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(stream_connect(&secondary_connection));
    CHECK(hal.stream.type == StreamType_Telnet && connection_changes == 2);
    clear_connection_output();
    hal.stream.write_all("online");
    CHECK(strcmp(secondary_output, "online") == 0);
    stream_disconnect(&secondary_connection);
    CHECK(stream_get_base() == fallback && hal.stream.type == StreamType_Null);
    CHECK(hal.stream.read() == SERIAL_NO_DATA && connection_changes == 3);
    clear_connection_output();
    hal.stream.write_all("offline");
    CHECK(secondary_output[0] == '\0');
    CHECK(stream_connect(&secondary_connection));
    CHECK(hal.stream.type == StreamType_Telnet && connection_changes == 4);
    clear_connection_output();
    hal.stream.write_all("reconnected");
    CHECK(strcmp(secondary_output, "reconnected") == 0);
    CHECK(stream_get_base() == fallback);
    return EXIT_SUCCESS;
}
