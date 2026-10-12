#include "support/engine_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t fixture = {0};
    settings_write_coord_data(CoordinateSystem_G59_3, &fixture);
    CHECK(!system_pos_at_fixture((point_2d_t){.x = 0, .y = 0}, Z_AXIS, CoordinateSystem_G59_3, -1));
    return EXIT_SUCCESS;
}
