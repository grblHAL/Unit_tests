#include "webui_host.h"
int main(void)
{
    char a[] = "SYNC", b[] = "srv1=clock.local", c[] = "zone=2";
    char *argv[] = {a, b, c, NULL};
    uint_fast16_t argc = 3;
    webui_trim_arg(&argc, argv, "srv1=");
    CHECK(argc == 2 && argv[0] == a && argv[1] == c && argv[2] == NULL);
    CHECK(strcmp(webui_get_arg(argc, argv, "zone="), "2") == 0);
    return 0;
}
