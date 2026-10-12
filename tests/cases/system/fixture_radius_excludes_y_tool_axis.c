#include "support/engine_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t fixture = {0};
    fixture.coord.x = 10;
    fixture.coord.y = 20;
    fixture.coord.z = 30;
    settings_write_coord_data(CoordinateSystem_G59_3, &fixture);
    point_2d_t position = {.x = 13, .y = 34};
    CHECK(system_pos_at_fixture(position, Y_AXIS, CoordinateSystem_G59_3, 5));
    CHECK(!system_pos_at_fixture(position, Y_AXIS, CoordinateSystem_G59_3, 4.99f));
    return EXIT_SUCCESS;
}
