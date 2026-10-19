#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G80X2", Status_GcodeAxisWordsExist);
    return EXIT_SUCCESS;
}
