#include "support/sleep_wait_host.h"
static unsigned alarm_notifications;
static void notify_motor_fault(sys_state_t state)
{
    CHECK(state == STATE_IDLE && ++alarm_notifications == 1);
    system_set_exec_alarm(Alarm_MotorFault);
}
int main(void)
{
    prepare_sleep_workflow();
    grbl.on_execute_realtime = notify_motor_fault;
    sleep_check();
    CHECK(alarm_notifications == 1 && sys.rt_exec_alarm == Alarm_MotorFault);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(sleep_free_space == 100 && sleep_coolant_output.flood);
    grbl.on_execute_realtime = protocol_execute_noop;
    engine_ticks += (uint32_t)(SLEEP_DURATION * 60000) + 1;
    engine_execute_tasks(STATE_IDLE);
    CHECK(sys.rt_exec_alarm == Alarm_MotorFault);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
