#include "support/json_host.h"
int main(void)
{
    json_out_t *json = json_start(json_file(), 2);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "name", "caf\xC3\xA9\n"));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"name\":\"caf\xC3\xA9\\n\"}") == 0);
    return EXIT_SUCCESS;
}
