#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_init_configured();
    bt_enable(false);
    bt_edge(true);
    CHECK(hal.stream.type == StreamType_Serial && !bt_welcomes && !bt_commands);
    bt_enable(true);
    bt_edge(false);
    bt_edge(true);
    CHECK(hal.stream.type == StreamType_Bluetooth && bt_welcomes == 1);
    return 0;
}
