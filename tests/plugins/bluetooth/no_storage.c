#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_storage_ok = false;
    bluetooth_init();
    bt_run();
    CHECK(!bt_settings && bt_warnings == 1 && !bt_commands);
    return 0;
}
