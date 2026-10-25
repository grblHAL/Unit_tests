#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bluetooth_init();
    bt_settings->load();
    bt_run();
    CHECK(bt_commands == 4 && bt_enabled() == 1);
    return 0;
}
