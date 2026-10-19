#include "support/mpg_stream_host.h"
int main(void)
{
    prepare_mpg_stream();
    CHECK(stream_mpg_register(&pendant_device, false, stream_mpg_check_enable));
    CHECK(registered_calls == 1 && pendant_tx_capable);
    CHECK(pendant_rt == stream_mpg_check_enable && !pendant_rx_disabled);
    primary_output[0] = pendant_output[0] = '\0';
    pendant_send_text("$G\n");
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output, "[GC:") != NULL && strstr(pendant_output, "ok" ASCII_EOL) != NULL);
    CHECK(primary_output[0] == '\0');
    CHECK(!sys.mpg_mode && hal.stream.read == primary_input);
    return EXIT_SUCCESS;
}
