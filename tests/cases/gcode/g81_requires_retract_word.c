#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G81Z-1F100") == Status_GcodeValueWordMissing);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
