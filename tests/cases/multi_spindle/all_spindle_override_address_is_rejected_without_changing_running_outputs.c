#include "support/spindle_address_rejection_host.h"
int main(void)
{
    check_running_spindles_reject_address("M51P0$-1", Status_NegativeValue);
    return EXIT_SUCCESS;
}
