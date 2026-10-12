#include "support/arc_limits_host.h"
#include "check.h"

int main(void)
{
    for(unsigned quadrant = 0; quadrant < 4; quadrant++)
        check_arc_quadrant(quadrant, (plane_t){ .axis_0 = 0, .axis_1 = 2, .axis_linear = 1 });
    return EXIT_SUCCESS;
}
