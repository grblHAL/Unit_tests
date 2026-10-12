#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    sys.driver_started = true;
    io_stream_t bluetooth = secondary_connection;
    bluetooth.type = StreamType_Bluetooth;
    CHECK(stream_connect(&bluetooth));
    CHECK(hal.stream.type == StreamType_Bluetooth);
    CHECK(strstr(secondary_output, "GrblHAL " GRBL_VERSION) != NULL);
    CHECK(strstr(primary_output, "BLUETOOTH STREAM ACTIVE") != NULL);
    return EXIT_SUCCESS;
}
