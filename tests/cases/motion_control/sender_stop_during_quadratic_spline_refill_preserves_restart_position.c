#include "support/curve_stop_stream_host.h"
int main(void)
{
    run_stopped_curve("G5.1X100Y100I0J100F100\nG1X200Y200\n");
    return EXIT_SUCCESS;
}
