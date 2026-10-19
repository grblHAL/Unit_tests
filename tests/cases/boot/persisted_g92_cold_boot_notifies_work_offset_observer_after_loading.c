#include "support/boot_coordinate_read_host.h"
int main(void)
{
    coordinate_saved_g92 = 2;
    run_coordinate_boot();
    CHECK(coordinate_read_failures == 0 && coordinate_wco_notifications == 1);
    NEAR(coordinate_seen_g54, 0);
    NEAR(coordinate_seen_g92, 2);
    NEAR(gc_state.g92_offset.coord.x, 2);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
