#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    spindle_ptrs_t spindle = {0};
    spindle_data_t data = {0};
    CHECK(!spindle_set_at_speed_range(&spindle, &data, 10000));
    spindle_validate_at_speed(data, 0);
    CHECK(data.state_programmed.at_speed);
    return EXIT_SUCCESS;
}
