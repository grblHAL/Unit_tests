#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press('I');
    key_press('i');
    key_press('j');
    CHECK(get_feed_override() == CMD_OVERRIDE_FEED_RESET &&
          get_feed_override() == CMD_OVERRIDE_FEED_COARSE_PLUS &&
          get_feed_override() == CMD_OVERRIDE_FEED_COARSE_MINUS);
    key_press('K');
    key_press('k');
    key_press('z');
    CHECK(get_spindle_override() == CMD_OVERRIDE_SPINDLE_RESET &&
          get_spindle_override() == CMD_OVERRIDE_SPINDLE_COARSE_PLUS &&
          get_spindle_override() == CMD_OVERRIDE_SPINDLE_COARSE_MINUS);
    key_press('M');
    key_press('C');
    CHECK(get_coolant_override() == CMD_OVERRIDE_COOLANT_MIST_TOGGLE &&
          get_coolant_override() == CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE);
    return 0;
}
