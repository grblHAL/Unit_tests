#include "support/boot_stream_motion_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 800;
    boot_hardware_position[1] = 0;
    boot_hardware_position[2] = 0;
    prepare_boot_stream_motion("G91G1X20F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    if(!boot_motion_full_planner_seen || !boot_motion_before_ack) fprintf(stderr, "Planner full=%u motion-before-ack=%u requested-blocks=%u available=%u\n",
        boot_motion_full_planner_seen, boot_motion_before_ack, settings.planner_buffer_blocks,
        (unsigned)plan_get_block_buffer_available());
    CHECK(boot_motion_full_planner_seen && boot_motion_before_ack);
    CHECK(sys.position[0] == 2400 && boot_motor_position[0] == 2400);
    CHECK(sys.position[1] == 0 && boot_motor_position[1] == 0);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    NEAR(gc_state.position[0], 30.0f);
    NEAR(gc_state.position[1], 0.0f);
    NEAR(gc_state.position[2], 0.0f);
    return EXIT_SUCCESS;
}
