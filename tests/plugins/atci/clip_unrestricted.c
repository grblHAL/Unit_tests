#include "atci_host.h"
int main(void)
{
    atci_start();
    float target[N_AXIS] = {20, 20, 42, 7};
    atci_clip(target);
    CHECK(clip_calls == 1);
    NEAR(target[2], 42);
    atci_flags(1);
    target[0] = -20;
    target[1] = -20;
    atci_clip(target);
    CHECK(clip_calls == 2);
    NEAR(target[0], -20);
    NEAR(target[3], 7);
    return 0;
}
