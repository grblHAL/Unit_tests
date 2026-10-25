#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_fail_command = BT_FAIL_COMMAND;
    bt_load();
    CHECK(!bt_enabled() && bt_commands == BT_FAIL_COMMAND &&
          strstr(bt_output, "configuration failed"));
    CHECK(bt_bauds == 2 && bt_baud[1] == 115200 && hal.stream.type == StreamType_Serial &&
          bt_base_handler == protocol_enqueue_realtime_command);
    return 0;
}
