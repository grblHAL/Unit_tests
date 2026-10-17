#include "support/curve_stop_stream_host.h"
int main(void)
{
    run_stopped_curve("G2X20Y20Z10I20F100\nG1X40Y40Z20\n");
    return EXIT_SUCCESS;
}
