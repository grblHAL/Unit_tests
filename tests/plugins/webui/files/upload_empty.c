#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {0};
    files_prepare(&request, &p);
    files_upload(&request, "empty.nc", "", 0, 7);
    files_readback("/empty.nc", "", 0);
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "empty.nc") && strstr(response, "\"size\":\"0 B\""));
    return 0;
}
