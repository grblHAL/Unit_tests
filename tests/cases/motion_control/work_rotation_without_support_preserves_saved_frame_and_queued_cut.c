#include "support/queued_motion_rejection_host.h"
int main(void)
{
    prepare_motion_program();
    coord_system_data_t before, after;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &before));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G10L2P1R45", Status_GcodeUnsupportedCommand);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &after));
    CHECK(memcmp(&before, &after, sizeof(before)) == 0);
    return EXIT_SUCCESS;
}
