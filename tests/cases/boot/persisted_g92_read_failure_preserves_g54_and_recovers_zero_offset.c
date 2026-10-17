#include "support/boot_coordinate_read_host.h"
int main(void)
{
    coordinate_saved_g54 = 5;
    coordinate_saved_g92 = 2;
    coordinate_failed_record = CoordinateSystem_G92;
    coordinate_fail_once = true;
    run_coordinate_boot();
    CHECK(coordinate_read_failures == 1);
    CHECK(strstr(engine_output, "error:7") != NULL);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 5);
    NEAR(gc_state.g92_offset.coord.x, 0);
    CHECK(coordinate_wco_notifications == 1);
    NEAR(coordinate_seen_g54, 5);
    NEAR(coordinate_seen_g92, 0);
    NEAR(coordinate_record_g92.coord.x, 0);
    return EXIT_SUCCESS;
}
