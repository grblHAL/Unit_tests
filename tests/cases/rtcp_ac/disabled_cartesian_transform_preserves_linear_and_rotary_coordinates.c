#include "support/rtcp_host.h"
int main(void)
{
    prepare_rtcp();
    coord_data_t target = {.values={91,92,93,94,95}}, position = {.values={1,-2,3,4,-5}};
    coord_data_t *result = kinematics.transform_from_cartesian(&target,&position);
    CHECK(result != NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(result->values[axis],position.values[axis]); NEAR(target.values[axis],91 + axis);
    }
    return EXIT_SUCCESS;
}
