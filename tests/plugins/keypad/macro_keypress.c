#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X3");
    CHECK(keypad.on_keypress_preview(CMD_MACRO_0, STATE_IDLE));
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X3\n"));
    CHECK(macro_statuses == 0 && macro_syncs == 0 && hal.stream.read == macro_serial_read);
    return 0;
}
