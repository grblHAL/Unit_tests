#include "support/canned_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_spindle();
    CHECK(canned_block("G84Z0R1F100") == Status_GcodeValueWordMissing);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
