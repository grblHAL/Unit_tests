#include "support/rtu_host.h"
#include "check.h"

int main(void)
{
    prepare_rtu();
    send_request();
    inject_reply(true);
    poll_rtu();
    CHECK(rx_calls == 0 && exceptions == 1);
    CHECK(exception_code == ModBus_CRCError);
    return EXIT_SUCCESS;
}
