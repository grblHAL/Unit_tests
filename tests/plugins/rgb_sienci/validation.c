#include "rgb_host.h"
int main(void)
{
    rgb_start();
    float invalid[][3] = {{-1, 1, 255},   {2, 1, 255}, {0.5f, 1, 255}, {0, -1, 255}, {0, 4, 255},
                          {0, 1.5f, 255}, {0, 1, -1},  {0, 1, 256},    {0, 1, 0.5f}};
    unsigned before = counts[0];
    for (unsigned i = 0; i < 9; i++)
        CHECK(rgb_command(invalid[i][0], invalid[i][1], invalid[i][2], false) ==
              Status_GcodeValueOutOfRange);
    CHECK(counts[0] == before);
    return 0;
}
