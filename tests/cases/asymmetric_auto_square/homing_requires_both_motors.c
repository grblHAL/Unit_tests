#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    CHECK(!kinematics.homing_cycle_validate((axes_signals_t){.bits = 1u << Y_AXIS}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.bits = (1u << Y_AXIS) | (1u << 3)}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.bits = 1u << X_AXIS}));
    return EXIT_SUCCESS;
}
