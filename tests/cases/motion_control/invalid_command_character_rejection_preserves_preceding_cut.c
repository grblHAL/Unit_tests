#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("&", Status_ExpectedCommandLetter);
    return EXIT_SUCCESS;
}
