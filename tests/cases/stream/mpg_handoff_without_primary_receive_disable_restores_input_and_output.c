#include "support/mpg_stream_host.h"

int main(void)
{
    prepare_report();
    state_set(STATE_IDLE);
    mpg_primary = primary_connection;
    mpg_primary.read = primary_input;
    mpg_primary.reset_read_buffer = reset_primary_input;
    mpg_primary.set_enqueue_rt_handler = mpg_primary_handler;
    CHECK(mpg_primary.disable_rx == NULL);
    pendant_rt = stream_mpg_check_enable;
    CHECK(stream_connect(&mpg_primary));
    CHECK(stream_mpg_register(&pendant_device, false, NULL));
    CHECK(stream_mpg_enable(true));
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg);
    CHECK(hal.stream.read == pendant_input);
    primary_output[0] = pendant_output[0] = 0;
    hal.stream.write("pendant reply");
    CHECK(strcmp(pendant_output, "pendant reply") == 0 && primary_output[0] == 0);
    CHECK(stream_mpg_enable(false));
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg);
    CHECK(hal.stream.read == primary_input && hal.stream.disable_rx == NULL);
    primary_output[0] = pendant_output[0] = 0;
    hal.stream.write("sender reply");
    CHECK(strcmp(primary_output, "sender reply") == 0 && pendant_output[0] == 0);
    return EXIT_SUCCESS;
}
