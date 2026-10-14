#include "support/wall_host.h"

int main(void)
{
    prepare_wall();
    settings.axis[X_AXIS].max_travel = -300;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    coord_data_t target = {.x = 150, .y = 200, .z = 3}, result;
    kinematics.transform_from_cartesian(&result, &target);
    NEAR(result.x, 250); NEAR(result.y, 250); NEAR(result.z, 3);
    NEAR(target.x, 150); NEAR(target.y, 200);
    return EXIT_SUCCESS;
}
