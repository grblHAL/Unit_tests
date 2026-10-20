#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(store_setting(Setting_DisableG92Persistence, "1") == Status_OK);
    CHECK(program_block("G92X5") == Status_OK);
    coord_system_data_t other = {0}; other.coord.x = 99;
    settings_write_coord_data(CoordinateSystem_G92, &other);
    grbl.on_wco_saved = record_end_coordinate;
    CHECK(program_block("M2") == Status_OK);
    CHECK(end_g92_saves == 0);
    coord_system_data_t saved = read_end_coordinate(CoordinateSystem_G92);
    NEAR(saved.coord.x, 99);
    return EXIT_SUCCESS;
}
