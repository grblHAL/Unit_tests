#include "support/segmented_stop_stream_host.h"
int main(void)
{
    run_stopped_program("G5X100Y100I0J100P-100Q0F100\nG1X200Y200\n");
    return EXIT_SUCCESS;
}
