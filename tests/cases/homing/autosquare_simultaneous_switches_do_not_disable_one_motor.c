#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    secondary_switch_steps = primary_switch_steps;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success);
    CHECK(squared_primary == 70 && squared_secondary == 70);
    CHECK(primary_stops == 0 && secondary_stops == 0);
    CHECK(!primary_disabled && !secondary_disabled);
    return EXIT_SUCCESS;
}
