#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {0};
    files_prepare(&request, &p);
    CHECK(vfs_mkdir("/jobs") == 0);
    files_upload(&request, "jobs/cut.nc", "G21\nM2\n", 7, 1024);
    files_readback("/jobs/cut.nc", "G21\nM2\n", 7);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "cut.nc") && strstr(response, "\"path\":\"/jobs\""));
    CHECK(strstr(response, "\"status\":\"ok\"") && p.headers == 1);
    return 0;
}
