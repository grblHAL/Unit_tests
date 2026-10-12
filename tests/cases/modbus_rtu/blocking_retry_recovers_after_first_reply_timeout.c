#include "support/rtu_blocking_host.h"

int main(void)
{
    prepare_rtu();
    reply_on_transmission = 2;
    CHECK(send_blocking_request(2));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
