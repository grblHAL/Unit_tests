#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_preview = true;
    key_press('R');
    CHECK(key_gcodes == 0);
    key_preview = false;
    key_press('R');
    CHECK(key_gcodes == 1);
    key_release();
    key_gcode_ok = false;
    key_press('L');
    key_release();
    CHECK(key_realtime_count == 1);
    return 0;
}
