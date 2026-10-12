#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); coord_system_data_t offset={0}; offset.rotation=90*RADDEG;
    settings_write_coord_data(CoordinateSystem_G55,&offset);
    queue_motion_program("G18G55G0X3Z4Y2");
    NEAR(gc_state.position[X_AXIS],4); NEAR(gc_state.position[Y_AXIS],2); NEAR(gc_state.position[Z_AXIS],-3);
    plan_block_t *block=plan_get_current_block(); CHECK(block!=NULL);
    NEAR(block->target_mm[X_AXIS],4); NEAR(block->target_mm[Y_AXIS],2); NEAR(block->target_mm[Z_AXIS],-3);
    return EXIT_SUCCESS;
}
