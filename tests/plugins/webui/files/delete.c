#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {.path = "/jobs", .filename = "cut.nc", .action = "delete"};
    files_prepare(&request, &p);
    CHECK(vfs_mkdir("/jobs") == 0);
    fatfs_put_file("/jobs/cut.nc", "M2\n", 3);
    fatfs_put_file("/jobs/keep.nc", "G0\n", 3);
    files_action(&request);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "cut.nc deleted") && !strstr(response, "\"name\":\"cut.nc\""));
    CHECK(strstr(response, "keep.nc") && strstr(response, "\"path\":\"/jobs\""));
    files_readback("/jobs/keep.nc", "G0\n", 3);
    files_action(&request);
    files_response(response, sizeof(response));
    CHECK(strstr(response, "cut.nc does not exist!") && !p.status[0]);
    return 0;
}
