#include "support/mpg_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    gc_state.file_run = true;
    CHECK(!stream_mpg_enable(true));
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg);
    CHECK(hal.stream.read == primary_input);
    CHECK(!primary_rx_disabled);
    CHECK(pendant_rx_disabled);
    return EXIT_SUCCESS;
}
