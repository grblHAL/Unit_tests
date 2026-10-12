#include "support/secondary_spindle_host.h"

int main(void)
{
    CHECK(!st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    prepare_spindle_motor();
    CHECK(!st2_motor_bind_spindle(X_AXIS, &settings.axis[X_AXIS]));
    CHECK(!st2_motor_bind_spindle(Y_AXIS, &settings.axis[Y_AXIS]));
    CHECK(!st2_motor_bind_spindle(Z_AXIS, &settings.axis[Z_AXIS]));
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    return EXIT_SUCCESS;
}
