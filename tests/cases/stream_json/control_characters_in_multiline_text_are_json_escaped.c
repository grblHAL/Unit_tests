#include "support/json_host.h"
int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "text", "first\nsecond\r\ntab\tform\fback\b"));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"text\":\"first\\nsecond\\r\\ntab\\tform\\fback\\b\"}") == 0);
    return EXIT_SUCCESS;
}
