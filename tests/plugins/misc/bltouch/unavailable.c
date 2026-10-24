#include "bltouch_host.h"
int main(void)
{
    claims_ok = false;
    load_bltouch();
    CHECK(!hal.driver_cap.bltouch_probe && warnings == 1 && outputs == 0 && delays == 0);
    hal.driver_reset();
    CHECK(resets == 1 && outputs == 0);
    return 0;
}
