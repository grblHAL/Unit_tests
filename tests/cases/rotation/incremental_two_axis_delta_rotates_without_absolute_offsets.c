#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); coord_system_data_t offset={0}; offset.rotation=90*RADDEG;
    settings_write_coord_data(CoordinateSystem_G55,&offset); queue_motion_program("G55G1X3Y4F100");
    queue_motion_program("G91G1X2Y0"); NEAR(gc_state.position[X_AXIS],-4); NEAR(gc_state.position[Y_AXIS],5);
    plan_block_t *last=plan_get_recent_block(); CHECK(last->steps.value[X_AXIS]==0); CHECK(last->steps.value[Y_AXIS]==160);
    return EXIT_SUCCESS;
}
