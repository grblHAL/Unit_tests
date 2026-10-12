#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); sys.position[0] = 800; sys.position[1] = -160; sys.position[2] = 40;
    plan_sync_position(); float *position = plan_get_position(); NEAR(position[0], 10); NEAR(position[1], -2); NEAR(position[2], .5f);
    return EXIT_SUCCESS;
}
