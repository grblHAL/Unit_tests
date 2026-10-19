#include "support/boot_coordinate_read_host.h"
int main(void)
{
    coordinate_saved_g54 = 5;
    coordinate_failed_record = CoordinateSystem_G54;
    coordinate_fail_once = true;
    run_coordinate_boot();
    CHECK(coordinate_read_failures == 1);
    CHECK(strstr(engine_output, "error:7") != NULL);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 0);
    NEAR(coordinate_record_g54.coord.x, 0);
    return EXIT_SUCCESS;
}
