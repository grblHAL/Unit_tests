#include "webui_host.h"
int main(void)
{
    char a[] = "SYNC", b[] = "dst=yes", c[] = "srv1=clock.local", d[] = "zone=2";
    char *argv[] = {a, b, c, d, NULL};
    uint_fast16_t argc = 4;
    CHECK(webui_get_arg(argc, argv, "SYNC") != NULL && webui_get_bool_arg(argc, argv, "dst="));
    CHECK(strcmp(webui_get_arg(argc, argv, "srv1="), "clock.local") == 0);
    webui_trim_arg(&argc, argv, "SYNC");
    webui_trim_arg(&argc, argv, "dst=");
    webui_trim_arg(&argc, argv, "srv1=");
    webui_trim_arg(&argc, argv, "zone=");
    CHECK(argc == 0 && argv[0] == NULL);
    return 0;
}
