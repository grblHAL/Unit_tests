#include "mpg_host.h"
int main(void)
{
    mpg_prepare();
    register_ok = false;
    hal.driver_cap.mpg_mode = 1;
    mpg_init();
    registered_settings->load();
    CHECK(warnings == 1 && claims == 1 && registrations == 1 && hal.driver_cap.mpg_mode);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "registered=NO"));
    return 0;
}
