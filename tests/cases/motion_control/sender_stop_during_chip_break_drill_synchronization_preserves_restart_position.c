#include "support/segmented_stop_stream_host.h"
int main(void)
{
    program_stop_in_drill = true;
    run_stopped_program("G91G73X1Z-5R1Q0.25L20F100\nG1X20\n");
    return EXIT_SUCCESS;
}
