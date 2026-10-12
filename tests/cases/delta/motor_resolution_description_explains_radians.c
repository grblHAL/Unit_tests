#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(strcmp(grbl.on_setting_get_description(Setting_AxisStepsPerMM + Y_AXIS), "Travel resolution in steps per radian (57.296 degrees).") == 0);
    CHECK(delta_description_calls == 0);
    return EXIT_SUCCESS;
}
