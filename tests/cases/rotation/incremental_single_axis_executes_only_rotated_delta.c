#include "support/motion_program_host.h"
#include <stdio.h>
#include "check.h"

int main(void)
{
    prepare_motion_program(); coord_system_data_t offset={0}; offset.rotation=90*RADDEG;
    settings_write_coord_data(CoordinateSystem_G55,&offset); queue_motion_program("G55G1X3Y4F100");
    queue_motion_program("G91G1X2"); execute_motion_program();
    if(physical_position[X_AXIS]!=-320 || physical_position[Y_AXIS]!=400)
        fprintf(stderr,"Physical endpoint: X=%ld Y=%ld steps\n",(long)physical_position[X_AXIS],(long)physical_position[Y_AXIS]);
    CHECK(physical_position[X_AXIS]==-320); CHECK(physical_position[Y_AXIS]==400);
    CHECK(axis_pulses[X_AXIS]==320); CHECK(axis_pulses[Y_AXIS]==400); CHECK(axis_pulses[Z_AXIS]==0);
    return EXIT_SUCCESS;
}
