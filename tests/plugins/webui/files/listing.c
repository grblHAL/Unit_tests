#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {.path = "/", .action = "list"};
    files_prepare(&request, &p);
    fatfs_put_file("/cut.nc", "G0X1\n", 5);
    CHECK(vfs_mkdir("/jobs") == 0);
    fatfs_put_file("/jobs/inside.nc", "M2\n", 3);
    files_action(&request);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(!p.status[0] && p.headers == 1);
    CHECK(strstr(response, "\"name\":\"cut.nc\"") && strstr(response, "\"size\":\"5 B\""));
    CHECK(strstr(response, "\"name\":\"jobs\"") && strstr(response, "\"size\":-1"));
    CHECK(!strstr(response, "inside.nc"));
    CHECK(strstr(response, "\"path\":\"/\"") && strstr(response, "\"status\":\"ok\""));
    CHECK(strstr(response, "\"total\"") && strstr(response, "\"occupation\""));
#if WEBUI_ENABLE == 2
    CHECK(strstr(response, "\"datetime\":\"\"") && strstr(response, "\"shortname\":\"cut.nc\""));
#else
    CHECK(strstr(response, "\"time\":\"2026-10-25T12:00:00"));
#endif
    return 0;
}
