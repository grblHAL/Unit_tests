#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_ptrs_t spindle = {.at_speed_tolerance = 5};
    spindle_data_t data = {0};
    CHECK(spindle_set_at_speed_range(&spindle, &data, 10000));
    NEAR(data.rpm_low_limit, 9500);
    CHECK(fabsf(data.rpm_high_limit - 10500) < .01f);
    NEAR(data.rpm_programmed, 10000);
    CHECK(!data.state_programmed.at_speed);
    return EXIT_SUCCESS;
}
