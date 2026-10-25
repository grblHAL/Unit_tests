#include "mpg_host.h"
int main(void)
{
    mpg_core_start();
    hal.stream.write_all("both");
    CHECK(strcmp(output, "both") == 0 && packets == 1);
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    CHECK(sent[0].size == 4 && memcmp(sent[0].data, "both", 4) == 0);
#else
    CHECK(sent[0].data[2] == MpgFrame_Dat && sent[0].data[3] == 4 &&
          memcmp(sent[0].data + 4, "both", 4) == 0);
#endif
    CHECK(stream_mpg_enable(true));
    output[0] = 0;
    packets = 0;
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 1
    mpg_up();
#endif
    hal.stream.write("pendant");
    CHECK(output[0] == 0 && packets == 1);
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    CHECK(sent[0].size == 7 && memcmp(sent[0].data, "pendant", 7) == 0);
#else
    CHECK(sent[0].data[3] == 7 && memcmp(sent[0].data + 4, "pendant", 7) == 0);
    mpg_ack(0);
#endif
    CHECK(stream_mpg_enable(false));
    unsigned before = packets;
    hal.stream.write("console");
    CHECK(strcmp(output, "console") == 0 && packets == before && proxy.get_tx_buffer_count() == 0);
    return 0;
}
