#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(2, "G0X4");
    macro_settings->save();
    macro_set_text(2, "G0X9");
    macro_settings->load();
    macro_run_mcode(2);
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X4\n"));
    memory[2048] ^= 1;
    macro_settings->load();
    macro_run_mcode(2);
    CHECK(hal.stream.read == macro_serial_read);
    return 0;
}
