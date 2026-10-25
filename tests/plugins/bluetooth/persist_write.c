#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_load();
    CHECK(bt_enabled() == 1 && bt_commands == 4);
    bt_name("Saved-CNC");
    bt_settings->save();
    FILE *f = fopen("bluetooth.nvs", "wb");
    CHECK(f && fwrite(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    return 0;
}
