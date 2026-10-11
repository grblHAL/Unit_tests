#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.homing.flags.enabled = settings.homing.flags.init_lock = true;
    sys.homing.mask = 1;
    sys.homed.mask = 0;
    sys.flags.travel_changed = true;
    grbl.on_file_demarcate(false);
    CHECK(!sys.flags.travel_changed);
    CHECK(sys.alarm == Alarm_HomingRequired);
    CHECK(state_get() == STATE_ALARM);
    CHECK(strstr(engine_output, "Homing cycle required") != NULL);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
