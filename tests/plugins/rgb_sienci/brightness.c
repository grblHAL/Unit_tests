#include "rgb_host.h"
int main(void)
{
    rgb_start();
    CHECK(rgb_command(0, 0, 37, true) == Status_OK);
    CHECK(brightness[0] == 37);
#if STATUS_LIGHT_ENABLE == 2
    CHECK(brightness[1] == 37);
#else
    CHECK(brightness[1] == 255);
#endif

    return 0;
}
