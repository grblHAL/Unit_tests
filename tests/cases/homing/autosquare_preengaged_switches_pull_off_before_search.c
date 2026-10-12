#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    squared_primary = 80; squared_secondary = 120;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success);
    CHECK(squared_primary == 70 && squared_secondary == 110);
    CHECK(!primary_disabled && !secondary_disabled);
    CHECK(wake_calls >= 5);
    return EXIT_SUCCESS;
}
