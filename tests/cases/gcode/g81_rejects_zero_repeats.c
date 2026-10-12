#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G81Z-1R0L0F100") == Status_NonPositiveValue);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
