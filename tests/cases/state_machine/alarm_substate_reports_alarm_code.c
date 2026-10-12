#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    sys.alarm = Alarm_HardLimit;
    state_set(STATE_ALARM);
    CHECK(state_get_substate() == Alarm_HardLimit);
    return EXIT_SUCCESS;
}
