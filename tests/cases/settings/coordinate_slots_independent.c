#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t first = {0}, second = {0}, result;
    first.coord.x = 12;
    second.coord.x = 34;
    settings_write_coord_data(CoordinateSystem_G54, &first);
    settings_write_coord_data(CoordinateSystem_G55, &second);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &result));
    NEAR(result.coord.x, 12);
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &result));
    NEAR(result.coord.x, 34);
    return EXIT_SUCCESS;
}
