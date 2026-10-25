#include "upload_host.h"
int main(void)
{
    http_request_t request = {0};
    CHECK(http_upload_start(&request, "grbl-upload", false) == NULL);
    CHECK(!request.private_data && !request.on_request_completed);
    return 0;
}
