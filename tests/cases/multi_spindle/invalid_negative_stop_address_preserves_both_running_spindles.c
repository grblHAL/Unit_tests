#include "support/spindle_address_rejection_host.h"
int main(void)
{
    check_running_spindles_reject_address("M5$-2", Status_GcodeValueOutOfRange);
    return EXIT_SUCCESS;
}
