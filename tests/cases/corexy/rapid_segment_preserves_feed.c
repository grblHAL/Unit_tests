#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "machine_limits.h"
#include "check.h"
void corexy_init(void);
int main(void)
{
    engine_prepare();
    limits_init();
    corexy_init();
    coord_data_t target = {.x = 10, .y = 3, .z = 2}, position = {0};
    plan_line_data_t data = {.feed_rate = 123};
    data.condition.rapid_motion = true;
    coord_data_t *result = kinematics.segment_line(&target, &position, &data, true);
    CHECK(result != NULL);
    NEAR(result->x, 13);
    NEAR(result->y, 7);
    NEAR(result->z, 2);
    NEAR(data.feed_rate, 123);
    CHECK(kinematics.segment_line(&target, &position, &data, false) != NULL);
    CHECK(kinematics.segment_line(&target, &position, &data, false) == NULL);
    return EXIT_SUCCESS;
}
