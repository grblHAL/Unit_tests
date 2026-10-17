#include "support/segmented_stop_stream_host.h"
int main(void)
{
    run_stopped_program("G91G81X1Z-1R0L40F100\nG1X20\n");
    return EXIT_SUCCESS;
}
