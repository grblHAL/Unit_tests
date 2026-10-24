#include "seal_host.h"
int main(void)
{
    seal_prepare();
    claim_ok = false;
    pneumaseal_init();
    CHECK(registered_settings);
    registered_settings->load();
    CHECK(claims == 1 && warnings == 1);
    seal_state(STATE_CYCLE);
    CHECK(!solenoid && outputs == 0);
    return 0;
}
