#include "support/segmented_hold_stream_host.h"
int main(void)
{
    run_held_program("G2X20Y20I20F100\nG91G1X1\n", 21, 20, 0);
    return EXIT_SUCCESS;
}
