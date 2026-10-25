#include "mpg_host.h"
int main(void)
{
    byte_only = true;
    mpg_start();
    proxy.write("G1");
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    CHECK(packets == 2 && sent[0].size == 1 && sent[0].data[0] == 'G' && sent[1].size == 1 &&
          sent[1].data[0] == '1');
#else
    CHECK(packets == 8);
    uint8_t frame[8];
    for (unsigned i = 0; i < packets; i++)
    {
        CHECK(sent[i].size == 1);
        frame[i] = sent[i].data[0];
    }
    CHECK(frame[0] == 2 && frame[2] == MpgFrame_Dat && frame[3] == 2 &&
          memcmp(frame + 4, "G1", 2) == 0);
    uint16_t crc = mpg_frame_crc16(frame + 1, 5);
    CHECK(frame[6] == (uint8_t)crc && frame[7] == (uint8_t)(crc >> 8));
#endif
    CHECK(proxy.get_tx_buffer_count() == 0 && claims == 1 && registrations == 1);
    return 0;
}
