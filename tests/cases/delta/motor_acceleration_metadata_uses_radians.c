#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisAcceleration, Z_AXIS), "rad/sec^2") == 0);
    CHECK(delta_unit_calls == 0);
    return EXIT_SUCCESS;
}
