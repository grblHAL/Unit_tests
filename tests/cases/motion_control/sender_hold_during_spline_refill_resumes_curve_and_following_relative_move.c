#include "support/curve_hold_stream_host.h"
int main(void)
{
    run_held_curve("G5X100Y100I0J100P-100Q0F100\nG91G1X1\n", 101, 100, 0);
    return EXIT_SUCCESS;
}
