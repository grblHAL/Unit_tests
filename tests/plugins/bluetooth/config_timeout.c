#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_timeout_command = 1;
    bt_load();
    CHECK(!bt_enabled() && bt_commands == 1 && strstr(bt_output, "configuration failed"));
    CHECK(bt_baud[bt_bauds - 1] == 115200 && bt_base_handler == protocol_enqueue_realtime_command);
    return 0;
}
