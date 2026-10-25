#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\nContent-Type: text/plain\r\n\r\nM2\n\r\n--grbl-upload--\r\n";
    for (unsigned i = 0; i < 2; i++)
    {
        http_request_t request;
        file_upload_t *upload = upload_begin(&request);
        upload_chunks(&request, body, sizeof(body) - 1, i ? 1 : sizeof(body));
        CHECK(upload->state == Upload_Complete && upload->uploaded == 3);
        upload_cleanup(&request);
        upload_readback("job.nc", "M2\n", 3);
    }
    return 0;
}
