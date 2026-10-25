#include "rgb_host.h"
int main(void)
{
    rgb_start();
    rgb_expect(0, 255, 255, 255);
    CHECK(writes[0] == 1);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(1, 255, 255, 255);
    CHECK(writes[1] == 1);
#endif

    return 0;
}
