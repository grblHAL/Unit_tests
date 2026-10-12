#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(!stream_mpg_register(NULL, false, NULL));
    CHECK(!stream_mpg_register(&secondary_connection, false, NULL));
    io_stream_t missing_callback = pendant_device;
    missing_callback.disable_rx = NULL;
    CHECK(!stream_mpg_register(&missing_callback, false, NULL));
    CHECK(registered_calls == 0);
    CHECK(!stream_mpg_enable(true));
    return EXIT_SUCCESS;
}
