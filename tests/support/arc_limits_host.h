#pragma once
#include "support/control_host.h"
#include "check.h"
#include <math.h>
/* Sample geometry independently of the core's quadrant/crossing algorithm.
   Test walls sit 0.5 mm away from cardinal extrema, avoiding sampling ambiguity. */
static bool sampled_arc_fits(double start, double sweep, plane_t plane, work_envelope_t *envelope)
{
    for(unsigned i = 0; i <= 4096; i++) {
        double angle = start + sweep * i / 4096;
        double x = -5 + 3 * cos(angle), y = -5 + 3 * sin(angle);
        if(x < envelope->min.values[plane.axis_0] || x > envelope->max.values[plane.axis_0] ||
           y < envelope->min.values[plane.axis_1] || y > envelope->max.values[plane.axis_1])
            return false;
    }
    return true;
}
static void check_arc_quadrant(unsigned quadrant, plane_t plane)
{
    const double pi = acos(-1.0);
    limits_init();
    sys.homed.mask = sys.soft_limits.mask = 7;
    for(unsigned end_quadrant = 0; end_quadrant < 4; end_quadrant++)
        for(unsigned endpoint = 0; endpoint < 3; endpoint++)
            for(int direction = -1; direction <= 1; direction += 2)
                for(unsigned wall = 0; wall < 5; wall++) {
                    double start_angle = pi / 4 + quadrant * pi / 2;
                    // Include short arcs within one quadrant, not only identical-endpoint circles.
                    double end_angle = pi / 12 + endpoint * pi / 6 + end_quadrant * pi / 2;
                    double sweep = end_angle - start_angle;
                    if(direction > 0 && sweep <= 0) sweep += 2 * pi;
                    if(direction < 0 && sweep >= 0) sweep -= 2 * pi;
                    coord_data_t start = {.values = {-5, -5, -5}}, end = start;
                    start.values[plane.axis_0] = -5 + 3 * cos(start_angle);
                    start.values[plane.axis_1] = -5 + 3 * sin(start_angle);
                    end.values[plane.axis_0] = -5 + 3 * cos(end_angle);
                    end.values[plane.axis_1] = -5 + 3 * sin(end_angle);
                    work_envelope_t envelope = {.min.values = {-10, -10, -10}, .max.values = {0, 0, 0}};
                    if(wall == 1) envelope.min.values[plane.axis_0] = -7.5f;
                    if(wall == 2) envelope.max.values[plane.axis_0] = -2.5f;
                    if(wall == 3) envelope.min.values[plane.axis_1] = -7.5f;
                    if(wall == 4) envelope.max.values[plane.axis_1] = -2.5f;
                    // These controls isolate arc extrema with valid endpoints; the
                    // out-of-range-endpoint G-code regression covers rejection separately.
                    if(!grbl.check_travel_limits(start.values, sys.soft_limits, true, &envelope) ||
                       !grbl.check_travel_limits(end.values, sys.soft_limits, true, &envelope))
                        continue;
                    bool expected = sampled_arc_fits(start_angle, sweep, plane, &envelope);
                    bool actual = grbl.check_arc_travel_limits(&end, &start, (point_2d_t){ .x = -5, .y = -5 }, 3, plane, direction, &envelope);
                    if(actual != expected)
                        fprintf(stderr, "start quadrant=%u end quadrant=%u endpoint=%u direction=%d wall=%u expected=%d actual=%d\n", quadrant+1, end_quadrant+1, endpoint, direction, wall, expected, actual);
                    CHECK(actual == expected);
                }
    }

