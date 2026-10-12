#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G81Z-1R-2F100") == Status_GcodeInvalidRetractPosition);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
