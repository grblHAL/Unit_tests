#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(true);
    corrupt_end_coordinate(CoordinateSystem_G54);
    CHECK(program_block("M30") == Status_OK);
    CHECK(program_complete_calls == 1 && program_completion_check_mode);
    CHECK(program_pallet_calls == 0);
    coord_system_data_t data;
    CHECK(!settings_read_coord_data(CoordinateSystem_G54, &data));
    return EXIT_SUCCESS;
}
