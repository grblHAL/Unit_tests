#include "webui_host.h"
int main(void)
{
    char a[] = "REFRESH", b[] = "/job.nc", c[] = "RELEASE";
    char *argv[] = {a, b, c, NULL};
    uint_fast16_t argc = 3;
    webui_trim_arg(&argc, argv, "REFRESH");
    CHECK(argc == 2 && argv[0] == b && argv[1] == c);
    webui_trim_arg(&argc, argv, "RELEASE");
    CHECK(argc == 1 && argv[0] == b && argv[1] == NULL);
    webui_trim_arg(&argc, argv, "absent");
    CHECK(argc == 1 && argv[0] == b);
    webui_trim_arg(&argc, argv, "/job.nc");
    CHECK(argc == 0 && argv[0] == NULL);
    return 0;
}
