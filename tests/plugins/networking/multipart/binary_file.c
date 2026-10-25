#include "multipart_host.h"
int main(void)
{
    upload_capture_t upload;
    upload_init(&upload);
    const char body[] = "--grbl-upload\r\nContent-Type: "
                        "application/octet-stream\r\n\r\n\x00\x80\xff\r\n--grbl-upload--\r\n";
    upload_feed(&upload, body, sizeof(body) - 1, 3);
    upload_complete(&upload, 1);
    const uint8_t expected[] = {0, 0x80, 0xff};
    CHECK(upload.parts[0].length == sizeof(expected) &&
          !memcmp(upload.parts[0].bytes, expected, sizeof(expected)));
    return 0;
}
