#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G51X0", Status_GcodeValueOutOfRange);
    return EXIT_SUCCESS;
}
