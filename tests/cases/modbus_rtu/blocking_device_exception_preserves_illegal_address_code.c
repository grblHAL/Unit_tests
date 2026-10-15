#include "support/rtu_exception_host.h"
#include "system.h"

int main(void)
{
    prepare_rtu();
    request_device_exception(2);
    CHECK(exception_frame_injected);
    CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 1);
    CHECK(exception_code == 2);
    return EXIT_SUCCESS;
}
