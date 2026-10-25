#include "macro_host.h"
int main(void)
{
    macro_irq_ok = false;
    macro_prepare();
    CHECK(macro_settings && macro_warnings == 1);
    macro_set_text(0, "G0X1");
    macro_run_mcode(0);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\n") && macro_statuses == 1);
    return 0;
}
