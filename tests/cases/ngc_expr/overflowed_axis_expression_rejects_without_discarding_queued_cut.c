#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G1X[EXP[100]]F100", Status_ExpressionInvalidResult);
    return EXIT_SUCCESS;
}
