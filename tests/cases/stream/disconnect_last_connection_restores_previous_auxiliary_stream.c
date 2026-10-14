#include "support/stream_three_host.h"
int main(void)
{
    prepare_three_streams();
    stream_disconnect(&third_connection);
    CHECK(hal.stream.type == StreamType_Telnet && hal.stream.write == secondary_write);
    clear_three_outputs();
    hal.stream.write_all("fixture");
    CHECK(strcmp(primary_output,"fixture") == 0 && strcmp(secondary_output,"fixture") == 0 && third_output[0] == 0);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
