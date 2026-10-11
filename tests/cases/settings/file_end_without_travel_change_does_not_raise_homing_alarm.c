#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.homing.flags.enabled = settings.homing.flags.init_lock = true;
    sys.homing.mask = 1;
    sys.homed.mask = 0;
    sys.flags.travel_changed = false;
    grbl.on_file_demarcate(false);
    CHECK(sys.alarm == Alarm_None);
    CHECK(file_callback_calls == 1);
    return EXIT_SUCCESS;
}
