#include "support/rtu_host.h"
#include "check.h"

int main(void)
{
    prepare_rtu();
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    CHECK(reply.rx_length == 7);
    CHECK(reply.adu[0] == 1 && reply.adu[1] == 3 && reply.adu[2] == 2);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
