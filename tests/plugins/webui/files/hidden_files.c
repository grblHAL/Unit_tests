#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {.path = "/", .action = "list"};
    files_prepare(&request, &p);
    fatfs_put_file("/visible.nc", "M2\n", 3);
    fatfs_put_file("/config.txt", "abc", 3);
    CHECK(vfs_chmod("/config.txt", (vfs_st_mode_t){.hidden = On}, (vfs_st_mode_t){.hidden = On}) ==
          0);
    files_action(&request);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "visible.nc"));
#if WEBUI_ENABLE == 2
    CHECK(strstr(response, "config.txt"));
#else
    CHECK(!strstr(response, "config.txt"));
#endif
    files_maintenance = true;
    files_action(&request);
    files_response(response, sizeof(response));
    CHECK(strstr(response, "visible.nc") && strstr(response, "config.txt"));
    files_readback("/config.txt", "abc", 3);
    return 0;
}
