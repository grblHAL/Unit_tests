#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] =
        "--grbl-upload\r\ncontent-disposition: form-data; name=\"file\"; "
        "filename=\"job.nc\"\r\ncOnTeNt-TyPe: text/plain\r\n\r\nM2\n\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 1);
    CHECK(upload->state == Upload_Complete && upload->uploaded == 3);
    upload_readback("job.nc", "M2\n", 3);
    upload_cleanup(&request);
    return 0;
}
