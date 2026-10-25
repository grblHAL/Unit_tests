#include "multipart_host.h"
int main(void)
{
    upload_capture_t upload;
    upload_init(&upload);
    const char body[] = "--grbl-upload\r\nContent-Disposition: form-data; name=\"file\"; "
                        "filename=\"job.nc\"\r\nContent-Type: "
                        "text/plain\r\n\r\nG21\r\nG1X5F200\r\n--grbl-upload--\r\n";
    upload_feed(&upload, body, sizeof(body) - 1, sizeof(body));
    upload_complete(&upload, 1);
    CHECK(!strcmp(upload.parts[0].fields, "Content-DispositionContent-Type"));
    CHECK(
        !strcmp(upload.parts[0].values, "form-data; name=\"file\"; filename=\"job.nc\"text/plain"));
    const char expected[] = "G21\r\nG1X5F200";
    CHECK(upload.parts[0].length == sizeof(expected) - 1 &&
          !memcmp(upload.parts[0].bytes, expected, sizeof(expected) - 1));
    return 0;
}
