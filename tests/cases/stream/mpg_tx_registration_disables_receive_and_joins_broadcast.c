#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(registered_calls == 1 && pendant_tx_capable);
    CHECK(pendant_rx_disabled);
    CHECK(!sys.mpg_mode);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write_all("status");
    CHECK(strcmp(primary_output, "status") == 0);
    CHECK(strcmp(pendant_output, "status") == 0);
    return EXIT_SUCCESS;
}
