#pragma once
#include "support/motion_program_host.h"
static unsigned arc_limit_calls;
static coord_data_t checked_arc_target, checked_arc_start;
static point_2d_t checked_arc_center;
static plane_t checked_arc_plane;
static float checked_arc_radius;
static int32_t checked_arc_turns;
static bool accept_arc(coord_data_t *target, coord_data_t *position, point_2d_t center,
                       float radius, plane_t plane, int32_t turns, work_envelope_t *envelope)
{
    CHECK(envelope == &sys.work_envelope);
    arc_limit_calls++;
    checked_arc_target = *target; checked_arc_start = *position;
    checked_arc_center = center; checked_arc_radius = radius;
    checked_arc_plane = plane; checked_arc_turns = turns;
    return true;
}
static inline void prepare_arc_limits_motion(void)
{
    prepare_motion_program();
    settings.limits.soft_enabled.mask = AXES_BITMASK;
    sys.soft_limits.mask = sys.homed.mask = AXES_BITMASK;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        sys.work_envelope.min.values[axis] = -2;
        sys.work_envelope.max.values[axis] = 2;
    }
    grbl.check_arc_travel_limits = accept_arc;
}
