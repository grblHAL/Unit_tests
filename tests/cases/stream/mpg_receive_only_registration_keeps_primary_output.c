#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, true, stream_mpg_check_enable));
    CHECK(registered_calls == 1 && !pendant_tx_capable);
    CHECK(pendant_rt == stream_mpg_check_enable);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write_all("status");
    CHECK(strcmp(primary_output, "status") == 0);
    CHECK(pendant_output[0] == '\0');
    return EXIT_SUCCESS;
}
