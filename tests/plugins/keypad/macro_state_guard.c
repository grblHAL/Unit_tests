#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X1");
    macro_state = STATE_HOLD;
    CHECK(keypad.on_keypress_preview(CMD_MACRO_0, STATE_HOLD));
    CHECK(hal.stream.read == macro_serial_read);
    macro_state = STATE_CHECK_MODE;
    macro_run_mcode(0);
    CHECK(macro_syncs == 0 && hal.stream.read == macro_serial_read);
    macro_state = STATE_IDLE;
    macro_run_mcode(0);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\n") && macro_syncs == 1);
    return 0;
}
