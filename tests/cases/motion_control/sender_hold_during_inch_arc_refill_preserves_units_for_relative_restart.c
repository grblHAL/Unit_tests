#include "support/curve_hold_stream_host.h"
int main(void)
{
    run_held_curve("G20G2X1Y1I1F4\nG91G1X0.1\n", 27.94f, 25.4f, 0);
    return EXIT_SUCCESS;
}
