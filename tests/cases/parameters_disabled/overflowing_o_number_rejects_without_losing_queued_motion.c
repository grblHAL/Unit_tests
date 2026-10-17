#include "support/queued_motion_rejection_host.h"
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    reject_without_losing_queued_motion("G20G91O4294967296G1X10F1", Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
