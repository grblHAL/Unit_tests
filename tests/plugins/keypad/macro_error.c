#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X1|G0X0");
    macro_run_mcode(0);
    CHECK(hal.stream.read() == 'G');
    CHECK(grbl.report.status_message(Status_GcodeValueOutOfRange) == Status_GcodeValueOutOfRange);
    CHECK(strstr(macro_output, "in macro") && macro_statuses == 1);
    CHECK(hal.stream.read == macro_serial_read && grbl.on_macro_return == NULL);
    macro_run_mcode(0);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\nG0X0\n") && macro_statuses == 2);
    return 0;
}
