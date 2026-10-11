#include "support/delta_api_host.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    settings.homing.pulloff = 2;
    coord_data_t reference;
    mpos_t zero_steps = {0};
    kinematics.transform_steps_to_cartesian(&reference, &zero_steps);
    grbl.on_homing_completed((axes_signals_t){.mask = 7}, true);
    NEAR(sys.home_position[X_AXIS], 0.0f);
    NEAR(sys.home_position[Y_AXIS], 0.0f);
    NEAR(sys.home_position[Z_AXIS], reference.z - 2);
    CHECK(delta_homing_calls == 1 && delta_homing_success);
    CHECK(delta_homing_axes.mask == 7);
    return EXIT_SUCCESS;
}
