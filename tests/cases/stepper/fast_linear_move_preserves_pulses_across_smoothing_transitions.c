#include "support/fast_motion_host.h"
int main(void)
{
    prepare_fast_motion();
    queue_motion_program("G1X300F12000");
    finish_fast_motion(0, 0, false);
    return EXIT_SUCCESS;
}
