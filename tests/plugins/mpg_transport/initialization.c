#include "mpg_host.h"
int main(void)
{
    mpg_start();
    CHECK(claims == 1 && registrations == 1 && hal.driver_cap.mpg_mode && saves == 1);
    CHECK(proxy.is_connected());
    CHECK(mpg_command(NULL) == Status_OK &&
          strstr(output, "claimed=yes,registered=yes,transport=framed,link=down"));
    mpg_init();
    CHECK(claims == 1 && registrations == 1);
    return 0;
}
