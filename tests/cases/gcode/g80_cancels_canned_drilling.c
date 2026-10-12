#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G81X1Z-1R0F100");
    execute_canned("G80");
    CHECK(!gc_state.modal.canned_cycle_active);
    execute_canned("G1X2F100");
    CHECK(sys.position[X_AXIS] == 160);
    CHECK(axis_pulses[Z_AXIS] == 160);
    return EXIT_SUCCESS;
}
