#include "support/soft_limit_motion_host.h"
int main(void)
{
    prepare_soft_limit_motion();
    queue_motion_program("G0X-6Y-49.5");
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == -480 && physical_position[Y_AXIS] == -3960);
    unsigned x_before = axis_pulses[X_AXIS], y_before = axis_pulses[Y_AXIS];
    // Exact radius5: start vector(4,-3), end vector(-3,-4), center(-10,-46.5).
    char arc[] = "G3X-13Y-50.5I-4J3F100";
    CHECK(gc_execute_block(arc) == Status_OK);
    if(!sys.abort) CHECK(protocol_buffer_synchronize());
    fprintf(stderr, "Arc limit: alarm=%u seen=%u endpoint=(%ld,%ld), allowed Y>=-50\n",
        (unsigned)sys.alarm, (unsigned)soft_alarm_seen,
        (long)physical_position[X_AXIS], (long)physical_position[Y_AXIS]);
    CHECK(soft_alarm_seen && sys.alarm == Alarm_SoftLimit);
    CHECK(physical_position[X_AXIS] == -480 && physical_position[Y_AXIS] == -3960);
    CHECK(axis_pulses[X_AXIS] == x_before && axis_pulses[Y_AXIS] == y_before);
    CHECK(sys.abort && !sys.position_lost && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
