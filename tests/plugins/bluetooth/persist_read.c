#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    FILE *f = fopen("bluetooth.nvs", "rb");
    CHECK(f && fread(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    bluetooth_init();
    bt_settings->load();
    bt_run();
    CHECK(bt_enabled() == 1 &&
          !strcmp(bt_setting(Setting_BlueToothDeviceName)->value, "Saved-CNC") && !bt_commands &&
          bt_irqs == 1);
    bt_edge(true);
    CHECK(hal.stream.type == StreamType_Bluetooth && hal.stream.is_connected());
    return 0;
}
