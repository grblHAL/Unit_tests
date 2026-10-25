#include "bt_host.h"
int main(void)
{
    bt_prepare(0, true);
    bluetooth_init();
    bt_run();
    CHECK(!bt_settings && !bt_claims && bt_warnings == 1 && strstr(bt_output, "no pin"));
    return 0;
}
