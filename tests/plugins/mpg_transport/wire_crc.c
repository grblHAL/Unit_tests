#include "mpg_host.h"
int main(void)
{
    CHECK(mpg_frame_crc16((const uint8_t *)"123456789", 9) == 0x29B1);
    mpg_start();
    proxy.write("G1");
    CHECK(packets == 1 && sent[0].size == 8 && sent[0].data[0] == 2 &&
          sent[0].data[2] == MpgFrame_Dat && sent[0].data[3] == 2 &&
          memcmp(sent[0].data + 4, "G1", 2) == 0);
    uint16_t crc = mpg_frame_crc16(sent[0].data + 1, 5);
    CHECK(sent[0].data[6] == (uint8_t)crc && sent[0].data[7] == (uint8_t)(crc >> 8));
    return 0;
}
