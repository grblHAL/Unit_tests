#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(strcmp(grbl.on_set_axis_setting_unit(Setting_AxisMaxTravel, X_AXIS), "fixture-unit") == 0);
    CHECK(delta_unit_calls == 1);
    return EXIT_SUCCESS;
}
