#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G1X[SQRT[", Status_ExpressionSyntaxError);
    return EXIT_SUCCESS;
}
