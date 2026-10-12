#include "support/rtu_host.h"
#include "check.h"

int main(void)
{
    prepare_rtu();
    send_request();
    for(unsigned tick = 0; tick < 500 && exceptions == 0; tick++) poll_rtu();
    CHECK(exceptions == 1);
    CHECK(rx_calls == 0);
    CHECK(tx_calls == 1);
    for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
    CHECK(exceptions == 1);
    return EXIT_SUCCESS;
}
