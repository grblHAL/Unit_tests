#include "macro_host.h"
int main(void)
{
    macro_storage = false;
    macro_prepare();
    CHECK(macro_settings == NULL && macro_warnings == 1);
    CHECK(grbl.user_mcode.check == NULL && keypad.on_keypress_preview == NULL);
    hal.driver_reset();
    CHECK(macro_resets == 1 && hal.stream.read == macro_serial_read);
    return 0;
}
