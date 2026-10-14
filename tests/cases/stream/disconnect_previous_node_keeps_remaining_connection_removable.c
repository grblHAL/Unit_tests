#include "support/stream_three_host.h"
int main(void)
{
    prepare_three_streams();
    stream_disconnect(&secondary_connection);
    stream_disconnect(&third_connection);
    clear_three_outputs();
    hal.stream.write_all("fixture");
    CHECK(strcmp(primary_output,"fixture") == 0 && secondary_output[0] == 0 && third_output[0] == 0);
    CHECK(hal.stream.write == primary_write);
    return EXIT_SUCCESS;
}
