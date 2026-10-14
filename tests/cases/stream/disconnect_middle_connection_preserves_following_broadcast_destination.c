#include "support/stream_three_host.h"
int main(void)
{
    prepare_three_streams();
    stream_disconnect(&secondary_connection);
    clear_three_outputs();
    hal.stream.write_all("fixture");
    CHECK(strcmp(primary_output,"fixture") == 0);
    CHECK(secondary_output[0] == 0 && strcmp(third_output,"fixture") == 0);
    stream_disconnect(&third_connection);
    return EXIT_SUCCESS;
}
