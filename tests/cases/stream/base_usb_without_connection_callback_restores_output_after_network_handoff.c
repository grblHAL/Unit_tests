#include "support/stream_connection_host.h"

int main(void)
{
    prepare_report();
    grbl.on_stream_changed = stream_changed;
    io_stream_t usb = primary_connection;
    usb.state.is_usb = true;
    usb.is_connected = NULL;
    CHECK(stream_connect(&usb));
    CHECK(stream_get_base() == &usb && hal.stream.state.is_usb);
    CHECK(hal.stream.is_connected != NULL && hal.stream.is_connected());
    CHECK(stream_connect(&secondary_connection));
    CHECK(hal.stream.type == StreamType_Telnet);
    clear_connection_output();
    hal.stream.write_all("both");
    CHECK(strcmp(primary_output, "both") == 0 && strcmp(secondary_output, "both") == 0);
    stream_disconnect(&usb);
    clear_connection_output();
    hal.stream.write_all("network");
    CHECK(primary_output[0] == 0 && strcmp(secondary_output, "network") == 0);
    CHECK(stream_connect(&usb));
    clear_connection_output();
    hal.stream.write_all("restored");
    CHECK(strcmp(primary_output, "restored") == 0 && strcmp(secondary_output, "restored") == 0);
    stream_disconnect(&secondary_connection);
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.state.is_usb);
    CHECK(hal.stream.is_connected != NULL && hal.stream.is_connected());
    CHECK(primary_rt == protocol_enqueue_realtime_command);
    clear_connection_output();
    hal.stream.write("reply");
    CHECK(strcmp(primary_output, "reply") == 0 && secondary_output[0] == 0);
    CHECK(connection_changes == 3);
    return EXIT_SUCCESS;
}
