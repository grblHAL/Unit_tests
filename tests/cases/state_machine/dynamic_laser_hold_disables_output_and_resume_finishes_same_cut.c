#include "support/laser_hold_host.h"
int main(void)
{
    start_laser_hold_move("G1X20F100M4S500");
    hold_laser_and_resume();
    return EXIT_SUCCESS;
}
