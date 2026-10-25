#include "multipart_host.h"
int main(void)
{
    upload_capture_t upload;
    upload_init(&upload);
    const char body[] =
        "--grbl-upload\r\nContent-Disposition: form-data; "
        "name=\"path\"\r\n\r\n/jobs\r\n--grbl-upload\r\nContent-Disposition: form-data; "
        "name=\"file\"; filename=\"cut.nc\"\r\n\r\nM2\n\r\n--grbl-upload--\r\n";
    upload_feed(&upload, body, sizeof(body) - 1, 7);
    upload_complete(&upload, 2);
    CHECK(!strcmp(upload.parts[0].values, "form-data; name=\"path\""));
    CHECK(upload.parts[0].length == 5 && !memcmp(upload.parts[0].bytes, "/jobs", 5));
    CHECK(!strcmp(upload.parts[1].values, "form-data; name=\"file\"; filename=\"cut.nc\""));
    CHECK(upload.parts[1].length == 3 && !memcmp(upload.parts[1].bytes, "M2\n", 3));
    return 0;
}
