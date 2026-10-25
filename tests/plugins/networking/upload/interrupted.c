#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] = "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
                        "filename=\"partial.nc\"\r\nContent-Type: text/plain\r\n\r\nG1X5\n";
    upload_chunks(&request, body, sizeof(body) - 1, 13);
    CHECK(upload->state == Upload_Write && upload->file.handle && upload->uploaded == 5);
    upload_cleanup(&request);
    CHECK(vfs_open("partial.nc", "r") == NULL);
    return 0;
}
