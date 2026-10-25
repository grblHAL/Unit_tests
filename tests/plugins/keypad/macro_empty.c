#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_run_mcode(0);
    CHECK(hal.stream.read == macro_serial_read && macro_statuses == 0);
    CHECK(keypad.on_keypress_preview(CMD_MACRO_0, STATE_IDLE));
    CHECK(hal.stream.read == macro_serial_read);
    CHECK(!keypad.on_keypress_preview('?', STATE_IDLE));
    return 0;
}
