#include "multipart_host.h"
int main(void)
{
    upload_capture_t upload;
    upload_init(&upload);
    const char body[] = "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
                        "filename=\"empty.nc\"\r\n\r\n\r\n--grbl-upload--\r\n";
    upload_feed(&upload, body, sizeof(body) - 1, 11);
    upload_complete(&upload, 1);
    CHECK(upload.parts[0].length == 0);
    return 0;
}
