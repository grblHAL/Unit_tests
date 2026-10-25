#include "mpg_host.h"
int main(void)
{
    mpg_prepare();
    claim_ok = false;
    mpg_init();
    CHECK(registered_settings);
    registered_settings->load();
    CHECK(warnings == 1 && claims == 1 && registrations == 0 && !hal.driver_cap.mpg_mode);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "claimed=NO"));
    return 0;
}
