#include "support/engine_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    state_set(STATE_CHECK_MODE);
    sys.suspend = true;
    sys.step_control.flags = 255;
    state_set(STATE_IDLE);
    CHECK(!sys.suspend);
    CHECK(sys.step_control.flags == 0);
    CHECK(sys.holding_state == Hold_NotHolding);
    CHECK(sys.parking_state == Parking_DoorClosed);
    return EXIT_SUCCESS;
}
