#include "support/laser_door_host.h"
int main(void)
{
    run_laser_door_program("G1X20F100M3S500");
    return EXIT_SUCCESS;
}
