#include "support/fast_motion_host.h"
int main(void)
{
    prepare_fast_motion();
    queue_motion_program("G1X300Y150Z75F12000");
    finish_fast_motion(150, 75, false);
    return EXIT_SUCCESS;
}
