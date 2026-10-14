#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_EEPROM);
    defaults_physical.put_byte(0, 0);
    CHECK(nvs_buffer_init());
    nvs_buffer_free(); hal.nvs = defaults_physical;
    coord_system_data_t coordinate;
    CHECK(settings_read_coord_data(CoordinateSystem_G59_3, &coordinate));
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(coordinate.coord.values[axis], 0);
    return EXIT_SUCCESS;
}
