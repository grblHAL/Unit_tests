#include "support/boot_coordinate_read_host.h"
int main(void)
{
    coordinate_saved_g54 = 5;
    run_coordinate_boot();
    CHECK(coordinate_read_failures == 0 && coordinate_wco_notifications == 1);
    NEAR(coordinate_seen_g54, 5);
    NEAR(coordinate_seen_g92, 0);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 5);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
