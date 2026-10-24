#include "mpg_host.h"
int main(void)
{
    mpg_core_start();
    const uint8_t request = CMD_STATUS_REPORT_LEGACY;
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    mpg_bytes(&request, 1);
#else
    mpg_receive(9, MpgFrame_Dat, &request, 1);
#endif
    CHECK(status_reports == 0 && proxy.get_rx_buffer_count() == 0);
    mpg_core_run();
    mpg_poll();
    CHECK(status_reports == 1 && !sys.mpg_mode && output[0] == 0);
    const char *expected = "<host-status>\n";
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    CHECK(packets == 1 && sent[0].size == strlen(expected) &&
          memcmp(sent[0].data, expected, strlen(expected)) == 0);
#else
    CHECK(packets == 2);
    unsigned data = 0, ack = 0;
    for (unsigned i = 0; i < packets; i++)
    {
        if (sent[i].data[2] == MpgFrame_Dat)
        {
            CHECK(sent[i].data[3] == strlen(expected) &&
                  memcmp(sent[i].data + 4, expected, strlen(expected)) == 0);
            data++;
            mpg_ack(i);
        }
        else
        {
            CHECK(sent[i].data[2] == MpgFrame_Ack && sent[i].data[1] == 9);
            ack++;
        }
    }
    CHECK(data == 1 && ack == 1 && proxy.get_tx_buffer_count() == 0);
#endif
    return 0;
}
