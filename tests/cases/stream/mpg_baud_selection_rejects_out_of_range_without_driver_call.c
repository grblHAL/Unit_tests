#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, true, NULL));
    CHECK(stream_mpg_set_baud(0));
    CHECK(pendant_baud == 38400);
    CHECK(stream_mpg_set_baud(5));
    CHECK(pendant_baud == 921600);
    CHECK(!stream_mpg_set_baud(6));
    CHECK(pendant_baud_calls == 2);
    CHECK(pendant_baud == 921600);
    return EXIT_SUCCESS;
}
