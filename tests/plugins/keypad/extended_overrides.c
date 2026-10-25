#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press(CMD_OVERRIDE_RAPID_EXTRA_LOW);
    CHECK(get_feed_override() == CMD_OVERRIDE_RAPID_EXTRA_LOW);
    key_press(CMD_OVERRIDE_SPINDLE_FINE_PLUS);
    CHECK(get_spindle_override() == CMD_OVERRIDE_SPINDLE_FINE_PLUS);
    key_press(CMD_OVERRIDE_FAN0_TOGGLE);
    CHECK(get_coolant_override() == CMD_OVERRIDE_FAN0_TOGGLE);
    return 0;
}
