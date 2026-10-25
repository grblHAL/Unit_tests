#include "multipart_host.h"
int main(void)
{
    upload_capture_t upload;
    upload_init(&upload);
    const char body[] = "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
                        "filename=\"a.nc\"\r\n\r\nG0X0\n\r\n--grbl-upload--\r\n";
    upload_feed(&upload, body, sizeof(body) - 1, 1);
    upload_complete(&upload, 1);
    CHECK(!strcmp(upload.parts[0].fields, "Content-Disposition"));
    CHECK(!strcmp(upload.parts[0].values, "form-data; name=\"file\"; filename=\"a.nc\""));
    CHECK(upload.parts[0].length == 5 && !memcmp(upload.parts[0].bytes, "G0X0\n", 5));
    return 0;
}
