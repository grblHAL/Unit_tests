#include "support/wall_host.h"
int main(void)
{
    prepare_wall();
    sys.driver_started = true;
    sys.position[X_AXIS] = 18000; sys.position[Y_AXIS] = 18500; sys.position[Z_AXIS] = 789;
    char value[] = "0.03";
    CHECK(settings_store_setting(Setting_JunctionDeviation,value) == Status_OK);
    NEAR(settings.junction_deviation,0.03f);
    fprintf(stderr,"motor counters after junction update: %ld,%ld,%ld\n",(long)sys.position[X_AXIS],(long)sys.position[Y_AXIS],(long)sys.position[Z_AXIS]);
    CHECK(sys.position[X_AXIS] == 18000 && sys.position[Y_AXIS] == 18500 && sys.position[Z_AXIS] == 789);
    return EXIT_SUCCESS;
}
