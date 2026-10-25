#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(1, "G0X2|");
    macro_run_mcode(1);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X2\n") && macro_statuses == 1);
    macro_set_text(1, "G0X0");
    macro_run_mcode(1);
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X0\n") && macro_statuses == 2);
    return 0;
}
