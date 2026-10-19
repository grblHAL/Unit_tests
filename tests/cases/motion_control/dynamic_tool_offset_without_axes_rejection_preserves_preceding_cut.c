#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G43.1", Status_GcodeG43DynamicAxisError);
    return EXIT_SUCCESS;
}
