#include "support/boot_stream_motion_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 10000;
    boot_hardware_position[1] = 10000;
    boot_hardware_position[2] = 0;
    prepare_boot_stream_motion("$J=G91X90F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    if(!boot_motion_full_planner_seen || !boot_motion_before_ack) fprintf(stderr, "Planner full=%u motion-before-ack=%u requested-blocks=%u available=%u\n",
        boot_motion_full_planner_seen, boot_motion_before_ack, settings.planner_buffer_blocks,
        (unsigned)plan_get_block_buffer_available());
    CHECK(boot_motion_full_planner_seen && boot_motion_before_ack);
    CHECK(sys.position[0] == 16341 && boot_motor_position[0] == 16341);
    CHECK(sys.position[1] == 6053 && boot_motor_position[1] == 6053);
    CHECK(sys.position[2] == 0 && boot_motor_position[2] == 0);
    /* Cable counter quantization permits a small Cartesian rounding difference. */
    CHECK(fabsf(gc_state.position[0] - 190.0f) < .02f);
    /* Cable counter quantization permits a small Cartesian rounding difference. */
    CHECK(fabsf(gc_state.position[1] - 75.0f) < .02f);
    /* Cable counter quantization permits a small Cartesian rounding difference. */
    CHECK(fabsf(gc_state.position[2] - 0.0f) < .02f);
    return EXIT_SUCCESS;
}
