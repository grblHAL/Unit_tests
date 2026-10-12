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
    sys.position[X_AXIS] = 800;
    sys.position[Y_AXIS] = 1600;
    sys.position[Z_AXIS] = -8000;
    CHECK(system_at_fixture(Z_AXIS, CoordinateSystem_G54, .01f));
    sys.position[Y_AXIS] += 80;
    CHECK(!system_at_fixture(Z_AXIS, CoordinateSystem_G54, .01f));
    return EXIT_SUCCESS;
}
