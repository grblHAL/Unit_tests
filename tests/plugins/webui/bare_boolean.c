#include "webui_host.h"
int main(void)
{
    char flag[] = "dst", other[] = "zone=2";
    char *argv[] = {flag, other, NULL};
    CHECK(webui_get_bool_arg(2, argv, "dst="));
    char *missing[] = {other, NULL};
    CHECK(!webui_get_bool_arg(1, missing, "dst="));
    CHECK(!webui_get_bool_arg(0, missing, "dst="));
    return 0;
}
