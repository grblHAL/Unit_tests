#include "support/mpg_stream_host.h"
static io_stream_t *registered_pendant;
static void remember_registered_pendant(io_stream_t *stream, bool tx_capable)
{
    pendant_registered(stream, tx_capable);
    registered_pendant = stream;
}
int main(void)
{
    prepare_mpg_stream();
    grbl.on_mpg_registered = remember_registered_pendant;
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(registered_pendant != NULL);
    stream_disconnect(registered_pendant);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write_all("status");
    CHECK(strcmp(primary_output, "status") == 0 && strcmp(pendant_output, "status") == 0);
    CHECK(stream_mpg_enable(true) && hal.stream.read == pendant_input);
    CHECK(stream_mpg_enable(false) && hal.stream.read == primary_input);
    return EXIT_SUCCESS;
}
