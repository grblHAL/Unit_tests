#include "webui_host.h"
int main(void)
{
    const char *truths[] = {"dst=yes", "dst=TrUe", "dst=1"};
    for (unsigned i = 0; i < 3; i++)
    {
        char value[16];
        strcpy(value, truths[i]);
        char *argv[] = {value, NULL};
        CHECK(webui_get_bool_arg(1, argv, "dst="));
    }
    const char *falsehoods[] = {"dst=no", "dst=false", "dst=0", "dst="};
    for (unsigned i = 0; i < 4; i++)
    {
        char value[16];
        strcpy(value, falsehoods[i]);
        char *argv[] = {value, NULL};
        CHECK(!webui_get_bool_arg(1, argv, "dst="));
    }
    return 0;
}
