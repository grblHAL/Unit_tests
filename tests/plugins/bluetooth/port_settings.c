#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bluetooth_init();
    bt_settings->restore();
    const setting_detail_t *d = bt_setting(Setting_BlueToothStateInput);
    setting_get_float_ptr get = (setting_get_float_ptr)d->get_value;
    CHECK(d->flags.reboot_required);
    CHECK(bt_port(0) == Status_OK && get(d->id) == 0);
    CHECK(bt_port(.5f) == Status_BadNumberFormat && get(d->id) == 0);
    CHECK(bt_port(2) == Status_AuxiliaryPortUnavailable && get(d->id) == 0);
    CHECK(bt_port(-1) == Status_OK && get(d->id) == -1);
    return 0;
}
