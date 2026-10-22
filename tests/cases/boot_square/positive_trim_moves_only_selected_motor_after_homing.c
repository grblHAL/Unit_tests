#include "support/boot_square_homing_host.h"
int main(void)
{
    square_trim = .25f;
    check_square_homing(false);
    return EXIT_SUCCESS;
}
