#include "support/rtu_blocking_host.h"

int main(void)
{
    prepare_rtu();
    corrupt_first_reply = true;
    CHECK(!send_blocking_request(0));
    CHECK(reply_injected && tx_calls == 1 && rx_calls == 0 && exceptions == 1);
    uint8_t reported = exception_code;
    reply_on_transmission = 2;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 1);
    CHECK(reply.adu[0] == 1 && reply.adu[1] == 3 && reply.adu[2] == 2 && reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    if(reported != ModBus_CRCError)
        fprintf(stderr, "Blocking corrupt reply reported %u, expected CRC error %u\n",
            (unsigned)reported, (unsigned)ModBus_CRCError);
    CHECK(reported == ModBus_CRCError);
    return EXIT_SUCCESS;
}
