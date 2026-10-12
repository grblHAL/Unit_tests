#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(completed_calls == 1 && homing_success);
    CHECK(squared_primary == 70 && squared_secondary == 110);
    CHECK(primary_stops > 0 && squared_disable_calls > 0);
    CHECK(!primary_disabled && !secondary_disabled);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
