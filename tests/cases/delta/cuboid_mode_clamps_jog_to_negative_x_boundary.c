#include "support/delta_api_host.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(delta_store(Setting_Kinematics7, "2") == Status_OK);
    sys.homed.mask = 7;
    float midz = (sys.work_envelope.min.z + sys.work_envelope.max.z) * 0.5f;
    float position[N_AXIS] = {0, 0, midz};
    float target[N_AXIS] = {sys.work_envelope.min.x + (-1 * 10), 0, midz};
    grbl.apply_travel_limits(target, position, &sys.work_envelope);
    NEAR(target[X_AXIS], sys.work_envelope.min.x);
    NEAR(target[Y_AXIS], 0.0f);
    NEAR(target[Z_AXIS], midz);
    return EXIT_SUCCESS;
}
