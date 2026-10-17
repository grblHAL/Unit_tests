#include "support/segmented_hold_stream_host.h"
int main(void)
{
    held_program_drilling = true;
    run_held_program("G91G83X1Z-5R1Q0.25L3F100\nG1X1\n", 4, 0, 1);
    return EXIT_SUCCESS;
}
