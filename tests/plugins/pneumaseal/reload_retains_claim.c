#include "seal_host.h"
int main(void)
{
    seal_start();
    CHECK(claims == 1);
    seal_setting(451, 9);
    registered_settings->save();
    seal_setting(451, 17);
    registered_settings->load();
    CHECK(claims == 1);
    seal_state(STATE_CYCLE);
    seal_state(STATE_IDLE);
    CHECK(timer_ms == 9000);
    return 0;
}
