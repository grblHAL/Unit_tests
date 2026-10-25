#include "multipart_host.h"
int main(void)
{
    multipartparser parser;
    multipartparser_callbacks callbacks;
    multipartparser_init(&parser, "grbl-upload");
    multipartparser_callbacks_init(&callbacks);
    CHECK(!callbacks.on_body_begin && !callbacks.on_part_begin && !callbacks.on_header_field &&
          !callbacks.on_header_value && !callbacks.on_headers_complete && !callbacks.on_data &&
          !callbacks.on_part_end && !callbacks.on_body_end);
    const char body[] = "--grbl-upload\r\nX-Job: demo\r\n\r\nG0X0\r\n--grbl-upload--\r\n";
    CHECK(multipartparser_execute(&parser, &callbacks, body, sizeof(body) - 1) == sizeof(body) - 1);
    return 0;
}
