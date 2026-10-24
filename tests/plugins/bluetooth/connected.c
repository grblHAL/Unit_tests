#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_init_configured();
    CHECK(!bt_commands && bt_irqs > 0 && hal.stream.type == StreamType_Serial);
    bt_edge(true);
    CHECK(hal.stream.type == StreamType_Bluetooth && hal.stream.is_connected() &&
          bt_welcomes == 1 && bt_base_disables == 1);
    bt_edge(false);
    CHECK(hal.stream.type == StreamType_Serial &&
          bt_base_handler == protocol_enqueue_realtime_command);
    return 0;
}
