#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.position[0] = 100; sys.position[1] = 200; sys.position[2] = 300;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = 7});
    CHECK(sys.position[0] == 0);
    CHECK(sys.position[1] == 0);
    CHECK(sys.position[2] == 0);
    return EXIT_SUCCESS;
}
