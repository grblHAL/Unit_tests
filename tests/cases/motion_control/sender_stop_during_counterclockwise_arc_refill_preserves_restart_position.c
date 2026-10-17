#include "support/segmented_stop_stream_host.h"
int main(void)
{
    run_stopped_program("G3X20Y20J20F100\nG1X40Y40\n");
    return EXIT_SUCCESS;
}
