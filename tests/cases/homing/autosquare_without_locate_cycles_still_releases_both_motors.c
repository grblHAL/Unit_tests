#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    settings.homing.locate_cycles = 0;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success);
    CHECK(squared_primary == 70 && squared_secondary == 110);
    CHECK(!primary_disabled && !secondary_disabled);
    return EXIT_SUCCESS;
}
