#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(1, "G0Y2");
    macro_action(1, 2);
    macro_state = STATE_CYCLE;
    macro_pin(1, false);
    CHECK(macro_realtime_count == 1 && macro_realtime[0] == CMD_FEED_HOLD);
    CHECK(hal.stream.read == macro_serial_read);
    macro_pin(1, true);
    CHECK(macro_realtime_count == 1);
    macro_action(1, 1);
    macro_pin(1, false);
    CHECK(macro_realtime_count == 2 && macro_realtime[1] == CMD_CYCLE_START);
    macro_action(1, 4);
    macro_pin(1, false);
    CHECK(macro_realtime_count == 3 && macro_realtime[2] == CMD_RESET);
    return 0;
}
