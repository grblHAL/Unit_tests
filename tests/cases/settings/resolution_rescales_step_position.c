#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    sys.position[X_AXIS] = 800;
    CHECK(store_setting(Setting_AxisStepsPerMM, "160") == Status_OK);
    NEAR(settings.axis[X_AXIS].steps_per_mm, 160);
    CHECK(sys.position[X_AXIS] == 1600);
    NEAR(gc_state.position[X_AXIS], 10);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
