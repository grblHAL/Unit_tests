#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X1|G1X0F50");
    macro_run_mcode(0);
    CHECK(hal.stream.read != macro_serial_read && macro_syncs == 1);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\nG1X0F50\n"));
    CHECK(hal.stream.read == macro_serial_read && macro_statuses == 1);
    CHECK(grbl.on_macro_return == NULL);
    return 0;
}
