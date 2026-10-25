#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {0};
    files_prepare(&request, &p);
    const uint8_t bytes[] = {0, 1, 0xff, '\r', '\n', 0, 42};
    files_upload(&request, "binary.nc", bytes, sizeof(bytes), 3);
    files_readback("/binary.nc", bytes, sizeof(bytes));
    char response[4096];
    files_response(response, sizeof(response));
    CHECK(strstr(response, "binary.nc") && strstr(response, "\"size\":\"7 B\""));
    CHECK(p.released > 10 && p.headers == 1);
    return 0;
}
