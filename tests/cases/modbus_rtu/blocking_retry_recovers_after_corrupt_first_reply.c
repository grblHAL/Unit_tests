#include "support/rtu_blocking_host.h"

int main(void)
{
    prepare_rtu();
    corrupt_first_reply = true;
    reply_on_transmission = 2;
    CHECK(send_blocking_request(2));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[0] == 1 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
