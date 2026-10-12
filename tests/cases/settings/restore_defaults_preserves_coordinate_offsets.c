#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    coord_system_data_t original = {0}, result;
    original.coord.x = 12;
    settings_write_coord_data(CoordinateSystem_G54, &original);
    settings_restore((settings_restore_t){ .defaults = true });
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    NEAR(result.coord.x, 12);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
