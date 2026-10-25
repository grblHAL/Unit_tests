#include "macro_host.h"
int main(void)
{
    macro_inputs = 0;
    macro_prepare();
    CHECK(macro_settings == NULL && macro_warnings == 1);
    CHECK(grbl.user_mcode.check == NULL && hal.stream.read == macro_serial_read);
    return 0;
}
