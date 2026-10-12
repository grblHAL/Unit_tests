#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t fixture = {0};
    fixture.coord.x = 10;
    fixture.coord.y = 20;
    settings_write_coord_data(CoordinateSystem_G54, &fixture);
    CHECK(system_pos_at_fixture((point_2d_t){.values = {13, 24}}, Z_AXIS, CoordinateSystem_G54, 5));
    CHECK(!system_pos_at_fixture((point_2d_t){.values = {13, 24}}, Z_AXIS, CoordinateSystem_G54, 4.99f));
    CHECK(!system_pos_at_fixture((point_2d_t){.values = {10, 20}}, Z_AXIS, CoordinateSystem_G54, 0));
    return EXIT_SUCCESS;
}
