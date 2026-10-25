#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X1|G0X0");
    macro_run_mcode(0);
    CHECK(hal.stream.read() == 'G');
    hal.driver_reset();
    CHECK(macro_resets == 1 && hal.stream.read == macro_serial_read);
    CHECK(grbl.on_macro_return == NULL && macro_statuses == 0);
    macro_run_mcode(0);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\nG0X0\n"));
    return 0;
}
