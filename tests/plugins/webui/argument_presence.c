#include "webui_host.h"
int main(void)
{
    char flag[] = "REFRESH", file[] = "/job.nc";
    char *argv[] = {flag, file, NULL};
    CHECK(webui_get_arg(2, argv, "REFRESH") == flag + strlen(flag));
    CHECK(webui_get_arg(2, argv, NULL) == flag);
    CHECK(webui_get_arg(2, argv, "RELEASE") == NULL);
    CHECK(webui_get_arg(0, argv, NULL) == NULL);
    CHECK(webui_get_arg(2, argv, "") == NULL);
    return 0;
}
