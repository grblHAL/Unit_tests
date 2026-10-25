#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {0};
    files_prepare(&request, &p);
    files_maintenance = true;
    files_upload(&request, "config.txt", "abc", 3, 17);
    vfs_stat_t stat;
    CHECK(vfs_stat("/config.txt", &stat) == 0 && stat.st_mode.hidden);
    files_readback("/config.txt", "abc", 3);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "config.txt"));
    return 0;
}
