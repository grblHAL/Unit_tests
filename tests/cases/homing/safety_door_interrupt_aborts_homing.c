#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    interrupt_request = EXEC_SAFETY_DOOR;
    CHECK(mc_homing_cycle((axes_signals_t){.bits = 1}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_HomingFailDoor);
    CHECK(sys.homed.bits == 0);
    CHECK(sys.abort);
    CHECK(reset_calls == 1);
    return EXIT_SUCCESS;
}
