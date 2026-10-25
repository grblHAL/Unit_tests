#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bluetooth_init();
    bt_settings->restore();
    CHECK(bt_port(0) == Status_OK);
    bt_name("Workshop-CNC");
    bt_settings->save();
    bt_settings->load();
    bt_run();
    CHECK(bt_enabled() == 1 && strstr(bt_command_log, "AT+NAME=Workshop-CNC\r\n"));
    return 0;
}
