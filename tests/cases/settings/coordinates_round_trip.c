#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t source = {0}, result;
    source.coord.x = 12.5f;
    source.coord.y = -3.25f;
    source.coord.z = 0.125f;
    settings_write_coord_data(CoordinateSystem_G54, &source);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    NEAR(result.coord.x, 12.5f);
    NEAR(result.coord.y, -3.25f);
    NEAR(result.coord.z, 0.125f);
    return EXIT_SUCCESS;
}
