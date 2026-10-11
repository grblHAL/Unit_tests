#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.homed.mask = 0;
    float target[N_AXIS] = {1000, 1000, 1000};
    float position[N_AXIS] = {0};
    grbl.apply_travel_limits(target, position, &sys.work_envelope);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(target[axis], 1000.0f);
    return EXIT_SUCCESS;
}
