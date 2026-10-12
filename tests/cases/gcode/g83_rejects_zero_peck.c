#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G83Z-1R0Q0F100") == Status_NegativeValue);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
