#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("O1.5", Status_GcodeCommandValueNotInteger);
    return EXIT_SUCCESS;
}
