#include "mpg_host.h"
int main(void)
{
    mpg_start();
    const uint8_t input = 'G';
    mpg_receive(1, MpgFrame_Dat, &input, 1);
    unsigned before = chains;
    grbl.on_execute_delay(STATE_IDLE);
    CHECK(chains == before + 1 && packets == 1 && sent[0].data[2] == MpgFrame_Ack);
    CHECK(proxy.read() == 'G' && proxy.read() == SERIAL_NO_DATA);
    proxy.write("ok\n");
    CHECK(packets == 2 && proxy.get_tx_buffer_count() == 3);
    now += 1000;
    grbl.on_execute_delay(STATE_IDLE);
    CHECK(chains == before + 2 && packets == 3 && sent[1].size == sent[2].size &&
          memcmp(sent[1].data, sent[2].data, sent[1].size) == 0);
    uint8_t type = MpgFrame_Dat;
    mpg_receive(sent[2].data[1], MpgFrame_Ack, &type, 1);
    grbl.on_execute_delay(STATE_IDLE);
    CHECK(chains == before + 3 && proxy.get_tx_buffer_count() == 0);
    return 0;
}
