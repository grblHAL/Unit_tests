#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G82Z-1R0F100") == Status_GcodeValueWordMissing);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
