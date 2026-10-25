#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"empty.nc\"\r\nContent-Type: text/plain\r\n\r\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 7);
    CHECK(upload->state == Upload_Complete && upload->uploaded == 0 && !upload->file.handle);
    upload_readback("empty.nc", "", 0);
    upload_cleanup(&request);
    return 0;
}
