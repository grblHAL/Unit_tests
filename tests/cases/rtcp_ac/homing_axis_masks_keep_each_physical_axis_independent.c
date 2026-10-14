#include "support/rtcp_host.h"
int main(void)
{
    prepare_rtcp();
    unsigned combined = 0;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        unsigned mask = kinematics.limits_get_axis_mask(axis);
        CHECK(mask == (1u << axis)); CHECK((combined & mask) == 0); combined |= mask;
    }
    CHECK(combined == AXES_BITMASK);
    return EXIT_SUCCESS;
}
