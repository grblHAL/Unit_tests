#include "support/mpg_observer_host.h"
int main(void)
{
    prepare_mpg_stream();
    io_stream_t input_only = pendant_device;
    input_only.write = NULL;
    CHECK(stream_mpg_register(&input_only,false,stream_mpg_check_enable));
    CHECK(registered_calls == 1 && !pendant_tx_capable);
    CHECK(pendant_rt == stream_mpg_check_enable);
    primary_output[0] = pendant_output[0] = 0;
    hal.stream.write_all("primary");
    CHECK(strcmp(primary_output,"primary") == 0 && pendant_output[0] == 0);
    return EXIT_SUCCESS;
}
