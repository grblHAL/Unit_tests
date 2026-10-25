#include "bt_host.h"
int main(void)
{
    bt_prepare(2, false);
    bluetooth_init();
    bt_settings->load();
    bt_run();
    CHECK(!bt_enabled() && !bt_irqs && !bt_commands && !bt_warnings);
    const setting_detail_t *d = bt_setting(Setting_BlueToothStateInput);
    CHECK(((setting_get_float_ptr)d->get_value)(d->id) == -1);
    return 0;
}
