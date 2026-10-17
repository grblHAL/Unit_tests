#include "support/engine_host.h"
#include "check.h"
int main(void)
{
    engine_parser_prepare();
    settings.homing.flags.enabled = true;
    settings.limits.soft_enabled.mask = sys.soft_limits.mask = sys.homed.mask = 1u << A_AXIS;
    work_envelope_t envelope = {0};
    envelope.min.values[A_AXIS] = -2;
    envelope.max.values[A_AXIS] = 2;
    coord_data_t start = {0}, target = {.x = 1, .y = 1};
    plane_t plane = {.axis_0 = X_AXIS, .axis_1 = Y_AXIS, .axis_linear = Z_AXIS};
    target.values[A_AXIS] = 3;
    CHECK(!grbl.check_arc_travel_limits(&target, &start, (point_2d_t){.y = 1}, 1, plane, 1, &envelope));
    target.values[A_AXIS] = -3;
    CHECK(!grbl.check_arc_travel_limits(&target, &start, (point_2d_t){.y = 1}, 1, plane, 1, &envelope));
    target.values[A_AXIS] = 2;
    CHECK(grbl.check_arc_travel_limits(&target, &start, (point_2d_t){.y = 1}, 1, plane, 1, &envelope));
    target.values[A_AXIS] = -2;
    CHECK(grbl.check_arc_travel_limits(&target, &start, (point_2d_t){.y = 1}, 1, plane, 1, &envelope));
    CHECK(plan_get_current_block() == NULL && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
