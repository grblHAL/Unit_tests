#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\nContent-Type: text/plain\r\n\r\nG21\nM2\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, sizeof(body));
    CHECK(upload->state == Upload_Complete && upload->uploaded == 7 && !upload->file.handle);
    upload_readback("job.nc", "G21\nM2\n", 7);
    upload_cleanup(&request);
    CHECK(fatfs_writes && fatfs_reads);
    return 0;
}
