#include "mpg_host.h"
int main(void)
{
    mpg_prepare();
    settings_ok = false;
    mpg_init();
    CHECK(warnings == 1 && !registered_settings && claims == 0);
    settings_ok = true;
    mpg_init();
    CHECK(registered_settings);
    registered_settings->load();
    CHECK(claims == 1);
    return 0;
}
