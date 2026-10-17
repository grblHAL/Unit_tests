#include "support/critical_alarm_host.h"
int main(void)
{
    lock_alarm = Alarm_EStop;
    lock_controls.e_stop = true;
    lock_release_after_callbacks = 2;
    run_critical_alarm_input("", 0);
    CHECK(lock_reset_requested_while_input_asserted);
    CHECK(realtime_calls >= 2 && !lock_controls.e_stop);
    CHECK(strstr(engine_output, "ALARM:10") != NULL);
    CHECK(sys.alarm == Alarm_EStop);
    return EXIT_SUCCESS;
}
