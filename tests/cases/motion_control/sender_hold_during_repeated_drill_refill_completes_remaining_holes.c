#include "support/segmented_hold_stream_host.h"
int main(void)
{
    run_held_program("G91G81X1Z-1R0L40F100\nG1X1\n", 41, 0, 0);
    return EXIT_SUCCESS;
}
