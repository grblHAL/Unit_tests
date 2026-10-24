#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(1);
    float starts[][2] = {{0, 30}, {60, 30}, {30, 0}, {30, 60}};
    float ends[][2] = {{60, 30}, {0, 30}, {30, 60}, {30, 0}};
    float expected[][2] = {{10, 30}, {50, 30}, {30, 10}, {30, 50}};
    for (unsigned i = 0; i < 4; i++)
    {
        position[0] = starts[i][0];
        position[1] = starts[i][1];
        float target[N_AXIS] = {ends[i][0], ends[i][1], 42, 7};
        atci_clip(target);
        NEAR(target[0], expected[i][0]);
        NEAR(target[1], expected[i][1]);
        NEAR(target[2], 42);
        NEAR(target[3], 7);
    }
    return 0;
}
