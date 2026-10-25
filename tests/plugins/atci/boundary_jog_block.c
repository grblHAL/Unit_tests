#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    position[0] = 10;
    position[1] = 30;
    float target[N_AXIS] = {20, 30, 5, 2};
    atci_clip(target);
    for (unsigned i = 0; i < N_AXIS; i++)
        NEAR(target[i], position[i]);
    CHECK(strstr(message, "blocked at keepout boundary"));
    return 0;
}
