#include "support/critical_alarm_host.h"
int main(void)
{
    lock_alarm = Alarm_MotorFault;
    lock_controls.motor_fault = true;
    lock_release_after_callbacks = 2;
    run_critical_alarm_input("", 0);
    CHECK(lock_reset_requested_while_input_asserted);
    CHECK(realtime_calls >= 2 && !lock_controls.motor_fault);
    CHECK(strstr(engine_output, "ALARM:17") != NULL);
    CHECK(sys.alarm == Alarm_MotorFault);
    return EXIT_SUCCESS;
}
