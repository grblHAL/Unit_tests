#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_uart_ok = false;
    bluetooth_init();
    bt_run();
    CHECK(!bt_settings && bt_claims == 1 && bt_warnings == 1 && strstr(bt_output, "no serial"));
    return 0;
}
