#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press('!');
    key_press('~');
    key_press('?');
    CHECK(key_realtime_count == 3 && key_realtime[0] == CMD_FEED_HOLD &&
          key_realtime[1] == CMD_CYCLE_START && key_realtime[2] == '?');
    key_state = STATE_ALARM;
    key_press('R');
    CHECK(!key_gcodes);
    key_press('X');
    CHECK(!strcmp(key_system, "$X"));
    key_press('H');
    CHECK(!strcmp(key_system, "$H"));
    return 0;
}
