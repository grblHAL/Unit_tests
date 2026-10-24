#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_enqueue('R');
    key_release();
    key_run();
    CHECK(key_gcodes == 0 && key_realtime_count == 0);
    key_press('R');
    CHECK(key_gcodes == 1);
    key_release();
    CHECK(key_realtime_count == 1 && key_realtime[0] == CMD_JOG_CANCEL);
    return 0;
}
