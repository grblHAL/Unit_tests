#include "support/dwell_sender_stop_host.h"
int main(void)
{
    run_dwell_sender_stop("G1X1Z-2F100\nG4P1\nG1X20\n");
    return EXIT_SUCCESS;
}
