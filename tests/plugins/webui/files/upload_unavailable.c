#include "files_host.h"
int main(void)
{
    http_request_t request;
    files_request_t p = {0};
    files_prepare(&request, &p);
    CHECK(fs_upload_handler(&request, fs_get_sd_drive()) == NULL);
    CHECK(!strcmp(p.status, "400 Bad Request") && !request.private_data);
    CHECK(!request.post_receive_data && !request.post_finished);
    p.content_type = "text/plain";
    CHECK(fs_upload_handler(&request, fs_get_sd_drive()) == NULL);
    CHECK(!strcmp(p.status, "400 Bad Request") && !request.private_data);
    return 0;
}
