#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {.path = "/", .filename = "cut.nc", .action = "delete", .quiet = "yes"};
    files_prepare(&request, &p);
    fatfs_put_file("/cut.nc", "M2\n", 3);
    files_action(&request);
    char response[16];
    files_response(response, sizeof(response));
    CHECK(!*response && !p.headers && !p.status[0]);
    vfs_stat_t stat;
    CHECK(vfs_stat("/cut.nc", &stat) != 0);
    return 0;
}
