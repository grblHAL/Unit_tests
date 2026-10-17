#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    pendant_rt = NULL; /* Driver starts unconfigured while pendant RX is disabled. */
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(pendant_rx_disabled);
    CHECK(stream_mpg_enable(true));
    CHECK(!pendant_rx_disabled && sys.mpg_mode);
    CHECK(stream_mpg_enable(false));
    CHECK(pendant_rx_disabled && !sys.mpg_mode);
    CHECK(hal.stream.read == primary_input && !primary_rx_disabled);
    return EXIT_SUCCESS;
}
