#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init();
    sys.homed.mask = sys.soft_limits.mask = 7;
    coord_data_t start = {.x = -2, .y = -5, .z = -5}, end = {.x = -5, .y = -2, .z = -5};
    plane_t plane = {.axis_0 = X_AXIS, .axis_1 = Y_AXIS, .axis_linear = Z_AXIS};
    work_envelope_t envelope = {.min.values = {-10, -10, -10}, .max.values = {0, 0, 0}};
    end.z = -11;
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, 1, &envelope));
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, -1, &envelope));
    end.z = -5;
    start.z = -11;
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, 1, &envelope));
    CHECK(!grbl.check_arc_travel_limits(&end, &start, (point_2d_t){.x=-5,.y=-5}, 3, plane, -1, &envelope));
    return EXIT_SUCCESS;
}
