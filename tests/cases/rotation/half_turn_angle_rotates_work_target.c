#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); coord_system_data_t offset={0}; offset.rotation=180*RADDEG;
    settings_write_coord_data(CoordinateSystem_G55,&offset); queue_motion_program("G55G1X3Y4F100");
    NEAR(gc_state.position[X_AXIS],-3); NEAR(gc_state.position[Y_AXIS],-4);
    return EXIT_SUCCESS;
}
