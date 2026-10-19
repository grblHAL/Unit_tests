#include "support/settings_host.h"
static axes_signals_t squared;
static axes_signals_t driver_ganged(bool auto_squared) { CHECK(auto_squared); return squared; }
int main(void)
{
    prepare_settings_store();
    CHECK(!settings_is_group_available(Group_Limits_DualAxis));
    hal.stepper.get_ganged = driver_ganged;
    CHECK(!settings_is_group_available(Group_Limits_DualAxis));
    squared.x = true;
    CHECK(settings_is_group_available(Group_Limits_DualAxis));
    return EXIT_SUCCESS;
}
