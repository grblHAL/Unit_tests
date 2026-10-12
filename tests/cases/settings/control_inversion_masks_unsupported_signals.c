#include "support/settings_host.h"
#include "check.h"
static control_signals_t no_controls(void) { return (control_signals_t){0}; }

int main(void)
{
    prepare_settings_store();
    hal.signals_cap.feed_hold = true;
    hal.control.get_state = no_controls;
    CHECK(store_setting(Setting_ControlInvertMask, "3") == Status_OK);
    CHECK(settings.control_invert.feed_hold);
    CHECK(!settings.control_invert.reset);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
