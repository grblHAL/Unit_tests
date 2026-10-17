#include "support/boot_coordinate_read_host.h"
int main(void)
{
    coordinate_g92_volatile = true;
    coordinate_saved_g92 = 2;
    run_coordinate_boot();
    NEAR(gc_state.g92_offset.coord.x, 0);
    NEAR(coordinate_record_g92.coord.x, 2);
    CHECK(coordinate_read_failures == 0 && coordinate_wco_notifications == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
