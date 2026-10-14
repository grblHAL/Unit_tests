#include "support/debug_external_host.h"
int main(void)
{
    engine_prepare();
    char text[180];
    memset(text,'x',sizeof(text)-1);
    text[179] = 0;
    debug_printf("%s",text);
    CHECK(strlen(external_output) == 98 + strlen(ASCII_EOL));
    CHECK(strspn(external_output,"x") == 98);
    CHECK(strcmp(external_output+98,ASCII_EOL) == 0);
    return 0;
}
