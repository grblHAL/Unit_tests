#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); char set[]="G10L2P2R90"; CHECK(gc_execute_block(set)==Status_OK);
    coord_system_data_t stored={0}; CHECK(settings_read_coord_data(CoordinateSystem_G55,&stored)); NEAR(stored.rotation,90*RADDEG);
    NEAR(gc_state.modal.g5x_offset.data.rotation,0); queue_motion_program("G55G1X3Y4F100");
    NEAR(gc_state.position[X_AXIS],-4); NEAR(gc_state.position[Y_AXIS],3);
    return EXIT_SUCCESS;
}
