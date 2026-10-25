#include "reference_host.h"
int main(void)
{
    uart_start();
    CHECK(reference_streams->streams[1].instance == 1 &&
          reference_streams->streams[1].flags.claimable);
    CHECK(serial2Init(9600) == NULL);
    uart2_start();
    CHECK(reference_streams->streams[1].flags.claimed && pins == 4 && clocks == 4);
    fprintf(stderr, "Registry instance=%u; returned instance=%u\n",
            reference_streams->streams[1].instance, uart2_stream->instance);
    CHECK(uart2_stream->instance == 1);
    return 0;
}
