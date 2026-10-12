#include "support/boot_host.h"
#include "check.h"
static unsigned clear_calls;
static void clear_fault(void) { CHECK(sys.alarm == Alarm_MotorFault); boot_control_signals.motor_fault = false; clear_calls++; boot_before_read = NULL; }
int main(void)
{
    boot_control_signals.motor_fault = true;
    boot_before_read = clear_fault;
    CHECK(grbl_enter() == 0);
    CHECK(clear_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "ALARM:17") != NULL);
    CHECK(strstr(engine_output, "Motor fault - clear, then reset to continue") != NULL);
    return EXIT_SUCCESS;
}
