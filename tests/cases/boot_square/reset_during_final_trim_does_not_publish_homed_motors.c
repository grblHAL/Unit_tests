#include "support/boot_square_homing_host.h"
int main(void)
{
    square_trim = .25f;
    reset_during_trim = true;
    check_square_homing(false);
    return EXIT_SUCCESS;
}
