#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    char text[180];
    memset(text,'x',179);
    text[179] = 0;
    debug_printf("%s",text);
    CHECK(strlen(debug_output) == 98 + strlen(ASCII_EOL));
    CHECK(strspn(debug_output,"x") == 98);
    CHECK(strcmp(debug_output+98,ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 1);
    return 0;
}
