#pragma once
#include "support/report_host.h"
#include "state_machine.h"
static inline void prepare_distance_report(coord_data_t position, coord_data_t target)
{
    prepare_report();
    state_set(STATE_IDLE);
    for(unsigned axis=0; axis<N_AXIS; axis++)
        sys.position[axis] = lroundf(position.values[axis] * settings.axis[axis].steps_per_mm);
    sync_position();
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    CHECK(plan_buffer_line(target.values, &data));
    settings.status_report.distance_to_go = true;
    settings.status_report.machine_position = true;
}
