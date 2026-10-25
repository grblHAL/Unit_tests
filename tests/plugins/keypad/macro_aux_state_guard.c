#include "macro_host.h"
int main(void)
{
    macro_prepare();
    macro_set_text(0, "G0X1");
    macro_state = STATE_HOLD;
    macro_pin(0, false);
    macro_run_tasks();
    CHECK(hal.stream.read == macro_serial_read);
    macro_state = STATE_IDLE;
    macro_pin(0, false);
    macro_state = STATE_HOLD;
    macro_run_tasks();
    CHECK(hal.stream.read == macro_serial_read);
    macro_state = STATE_IDLE;
    macro_pin(0, false);
    macro_run_tasks();
    char text[128];
    macro_read_text(text, sizeof(text));
    CHECK(!strcmp(text, "G0X1\n"));
    return 0;
}
