#include "support/json_host.h"
int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "path", "C:\\jobs\\workbee.nc"));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"path\":\"C:\\\\jobs\\\\workbee.nc\"}") == 0);
    return EXIT_SUCCESS;
}
