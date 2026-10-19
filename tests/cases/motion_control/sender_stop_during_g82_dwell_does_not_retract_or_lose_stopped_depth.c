#include "support/dwell_sender_stop_host.h"
int main(void)
{
    run_dwell_sender_stop("G82X1Z-2R0P1F100\nG1X20\n");
    return EXIT_SUCCESS;
}
