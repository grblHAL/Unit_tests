#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    coord_system_data_t original = {0}, result;
    original.coord.x = 12; original.coord.y = -3;
    settings_write_coord_data(CoordinateSystem_G54, &original);
    settings_restore((settings_restore_t){ .startup_lines = true });
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    NEAR(result.coord.x, 12); NEAR(result.coord.y, -3);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
