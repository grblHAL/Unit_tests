#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    sys.alarm = Alarm_HardLimit;
    sys.suspend = true;
    state_set(STATE_CHECK_MODE);
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(sys.alarm == Alarm_None);
    CHECK(!sys.suspend);
    return EXIT_SUCCESS;
}
