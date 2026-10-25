#include "rgb_host.h"
int main(void)
{
    rgb_start();
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(pending == 1);
    for (unsigned i = 0; i < 10; i++)
        rgb_run_next();
    CHECK(!pending);
    rgb_expect(0, 255, 255, 255);
    CHECK(now == 1350);
    return 0;
}
