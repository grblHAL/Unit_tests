#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\nContent-Type: text/plain\r\n\r\nG0X0\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 1);
    CHECK(upload->state == Upload_Complete && upload->uploaded == 5);
    upload_readback("job.nc", "G0X0\n", 5);
    upload_cleanup(&request);
    return 0;
}
