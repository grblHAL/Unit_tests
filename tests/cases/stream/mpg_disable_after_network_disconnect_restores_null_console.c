#include "support/mpg_stream_host.h"

int main(void)
{
    prepare_report();
    state_set(STATE_IDLE);
    const io_stream_t *fallback = stream_null_init(115200);
    CHECK(stream_connect(fallback));
    CHECK(stream_connect(&secondary_connection));
    stream_disconnect(&secondary_connection);
    CHECK(stream_get_base() == fallback && hal.stream.type == StreamType_Null);
    CHECK(hal.stream.read == fallback->read && hal.stream.write == fallback->write);
    pendant_rt = stream_mpg_check_enable;
    sys.driver_started = true;
    CHECK(stream_mpg_register(&pendant_device, false, stream_mpg_check_enable));
    CHECK(stream_mpg_enable(true));
    CHECK(sys.mpg_mode && hal.stream.state.is_mpg && hal.stream.read == pendant_input);
    CHECK(!pendant_rx_disabled && pendant_rt == protocol_enqueue_realtime_command);
    CHECK(stream_mpg_enable(false));
    CHECK(!sys.mpg_mode);
    bool reader_restored = hal.stream.read == fallback->read;
    bool writer_restored = hal.stream.write == fallback->write;
    bool mode_restored = !hal.stream.state.is_mpg;
    bool receiver_restored = pendant_rx_disabled;
    bool handler_restored = pendant_rt == stream_mpg_check_enable;
    fprintf(stderr, "Null-console release: reader=%u writer=%u mode=%u rx=%u handler=%u\n",
        reader_restored, writer_restored, mode_restored, receiver_restored, handler_restored);
    CHECK(stream_connect(&secondary_connection));
    secondary_output[0] = '\0';
    hal.stream.write("reconnected");
    CHECK(strcmp(secondary_output, "reconnected") == 0);
    CHECK(stream_get_base() == fallback && hal.stream.type == StreamType_Telnet);
    CHECK(reader_restored && writer_restored && mode_restored);
    CHECK(receiver_restored && handler_restored);
    return EXIT_SUCCESS;
}
