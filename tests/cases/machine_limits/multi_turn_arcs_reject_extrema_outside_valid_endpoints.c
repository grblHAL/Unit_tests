#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init();
    sys.homed.mask = sys.soft_limits.mask = 7;
    coord_data_t start = {.x = -2, .y = -5, .z = -5}, end = {.x = -5, .y = -2, .z = -5};
    plane_t plane = {.axis_0 = X_AXIS, .axis_1 = Y_AXIS, .axis_linear = Z_AXIS};
    work_envelope_t envelope = {.min.values = {-10, -10, -10}, .max.values = {0, 0, 0}};
    envelope.min.x = -7.5f;
    CHECK(grbl.check_travel_limits(start.values, sys.soft_limits, true, &envelope));
    CHECK(grbl.check_travel_limits(end.values, sys.soft_limits, true, &envelope));
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, 2, &envelope));
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, -2, &envelope));
    return EXIT_SUCCESS;
}
