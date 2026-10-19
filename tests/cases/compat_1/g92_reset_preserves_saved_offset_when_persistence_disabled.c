#include "support/program_end_host.h"
int main(void)
{
    prepare_program_end(false);
    coord_system_data_t saved = {0};
    saved.coord.values[X_AXIS] = 3;
    saved.coord.values[Y_AXIS] = -4;
    settings_write_coord_data(CoordinateSystem_G92, &saved);
    char persistence[] = "1";
    CHECK(settings_store_setting(Setting_DisableG92Persistence, persistence) == Status_OK);
    CHECK(program_block("G92X5Y-2") == Status_OK);
    CHECK(program_block("G92.1") == Status_OK);
    CHECK(!gc_state.g92_offset_applied);
    CHECK(settings_read_coord_data(CoordinateSystem_G92, &saved));
    NEAR(saved.coord.values[X_AXIS], 3);
    NEAR(saved.coord.values[Y_AXIS], -4);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.g92_offset.coord.values[axis], 0);
    return EXIT_SUCCESS;
}
