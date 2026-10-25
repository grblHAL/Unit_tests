#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    char percentage[] = "1", minimum[] = "2", maximum[] = "5";
    CHECK(settings_store_setting(Setting_DualAxisLengthFailPercent, percentage) == Status_OK);
    CHECK(settings_store_setting(Setting_DualAxisLengthFailMin, minimum) == Status_OK);
    CHECK(settings_store_setting(Setting_DualAxisLengthFailMax, maximum) == Status_OK);
    char home[] = "$HX";
    CHECK(system_execute_line(home, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success && completed_calls == 1);
    CHECK(squared_primary == 70 && squared_secondary == 110);
    CHECK(primary_stops > 0 && !primary_disabled && !secondary_disabled);
    CHECK(!squared_switches().a.x && !squared_switches().b.x);
    CHECK(reset_calls == 0 && sys.alarm == Alarm_None && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
