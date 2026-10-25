#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    position[0] = 20;
    position[1] = 20;
    position[2] = 9;
    position[3] = 3;
    CHECK(!atci_check(0, 0));
    float target[N_AXIS] = {0, 0, 30, 7};
    atci_clip(target);
    for (unsigned i = 0; i < N_AXIS; i++)
        NEAR(target[i], position[i]);
    CHECK(strstr(message, "inside the keepout"));
    return 0;
}
