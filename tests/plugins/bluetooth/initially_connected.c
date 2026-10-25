#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_pin_high = true;
    bt_init_configured();
    CHECK(!bt_commands && hal.stream.type == StreamType_Bluetooth && bt_welcomes == 1);
    CHECK(hal.stream.is_connected());
    return 0;
}
