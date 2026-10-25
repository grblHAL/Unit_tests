#include "macro_host.h"
int main(void)
{
    macro_prepare();
    CHECK(macro_warnings == 0);
    macro_set_text(0, "G0X1");
    macro_set_text(1, "G0Y2");
    macro_pin(0, true);
    macro_run_tasks();
    CHECK(hal.stream.read == macro_serial_read);
    macro_pin(0, false);
    CHECK(hal.stream.read == macro_serial_read);
    macro_run_tasks();
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\n"));
    macro_pin(1, false);
    macro_run_tasks();
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0Y2\n"));
    CHECK(macro_statuses == 0 && macro_syncs == 0);
    return 0;
}
