#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.position[0] = 100; sys.position[1] = 200; sys.position[2] = 300;
    kinematics.limits_set_target_pos(1);
    CHECK(sys.position[0] == 100);
    CHECK(sys.position[1] == 0);
    CHECK(sys.position[2] == 300);
    return EXIT_SUCCESS;
}
