#include "support/segmented_hold_stream_host.h"
int main(void)
{
    run_held_program("G5.1X100Y100I0J100F100\nG91G1X1\n", 101, 100, 0);
    return EXIT_SUCCESS;
}
