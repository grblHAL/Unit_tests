#include "mpg_host.h"
static void receive(uint8_t seq, const char *text)
{
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    (void)seq;
    mpg_bytes((const uint8_t *)text, strlen(text));
#else
    mpg_receive(seq, MpgFrame_Dat, (const uint8_t *)text, strlen(text));
#endif
}
int main(void)
{
    mpg_core_start();
    CHECK(stream_open_instance(1, 115200, NULL, "Taken UART") == NULL && claims == 1);
    CHECK(!sys.mpg_mode && !hal.stream.state.is_mpg && hal.stream.type == StreamType_Null);
    receive(1, "G1\n");
    CHECK(proxy.get_rx_buffer_count() == 0 && hal.stream.read() == SERIAL_NO_DATA);
    core_state = STATE_CYCLE;
    CHECK(!stream_mpg_enable(true) && !sys.mpg_mode);
    core_state = STATE_IDLE;
    CHECK(stream_mpg_enable(true) && sys.mpg_mode && hal.stream.state.is_mpg);
    receive(2, "G1!\n");
    CHECK(hal.stream.read() == 'G' && hal.stream.read() == '1' && hal.stream.read() == '\n' &&
          hal.stream.read() == SERIAL_NO_DATA);
    CHECK(stream_mpg_set_baud(4) && baud == 576000);
    CHECK(!stream_mpg_set_baud(6) && baud == 576000);
    CHECK(stream_mpg_enable(false) && !sys.mpg_mode && !hal.stream.state.is_mpg &&
          hal.stream.type == StreamType_Null);
    receive(3, "G0\n");
    CHECK(proxy.get_rx_buffer_count() == 0 && hal.stream.read() == SERIAL_NO_DATA);
    CHECK(mode_reports == 2 && registrations == 1 && claims == 1);
    return 0;
}
