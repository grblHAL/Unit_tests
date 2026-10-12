#include "support/arc_limits_host.h"
#include "check.h"

int main(void)
{
    check_arc_quadrant(2, (plane_t){ .axis_0 = X_AXIS, .axis_1 = Y_AXIS, .axis_linear = Z_AXIS });
    return EXIT_SUCCESS;
}
