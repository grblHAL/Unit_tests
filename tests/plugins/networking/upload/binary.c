#include "upload_host.h"
int main(void)
{
    fatfs_prepare();
    http_request_t request;
    file_upload_t *upload = upload_begin(&request);
    const char body[] = "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
                        "filename=\"job.bin\"\r\nContent-Type: "
                        "application/octet-stream\r\n\r\n\x00\x80\xff\r\n--grbl-upload--\r\n";
    upload_chunks(&request, body, sizeof(body) - 1, 3);
    const uint8_t expected[] = {0, 0x80, 0xff};
    CHECK(upload->state == Upload_Complete && upload->uploaded == sizeof(expected));
    upload_readback("job.bin", expected, sizeof(expected));
    upload_cleanup(&request);
    return 0;
}
