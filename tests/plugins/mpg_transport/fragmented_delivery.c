#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t frame[MPG_TRANSPORT_MAX_FRAME];
    uint8_t payload[] = {'G', '1'};
    size_t n = mpg_frame_build(frame, 1, MpgFrame_Dat, payload, 2);
    mpg_bytes(frame, n - 1);
    CHECK(proxy.get_rx_buffer_count() == 0 && rt_calls == 0);
    mpg_bytes(frame + n - 1, 1);
    CHECK(proxy.get_rx_buffer_count() == 2 && rt_calls == 2);
    return 0;
}
