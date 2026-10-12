#include "support/rtu_blocking_host.h"

int main(void)
{
    prepare_rtu();
    CHECK(!send_blocking_request(2));
    CHECK(tx_calls == 3 && rx_calls == 0 && exceptions == 1);
    CHECK(exception_code == ModBus_Timeout);
    return EXIT_SUCCESS;
}
