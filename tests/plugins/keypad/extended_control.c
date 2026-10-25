#include "key_host.h"
int main(void)
{
    key_prepare();
    key_load();
    key_press(CMD_CYCLE_START);
    key_press(CMD_SOFT_ESTOP);
    key_press(CMD_STATUS_REPORT);
    CHECK(key_realtime_count == 3 && key_realtime[0] == CMD_CYCLE_START &&
          key_realtime[1] == CMD_SOFT_ESTOP && key_realtime[2] == CMD_STATUS_REPORT);
    CHECK(key_reports == 1);
    return 0;
}
