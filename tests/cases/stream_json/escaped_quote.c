#include "support/json_host.h"
#include "check.h"

int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "value", "a\"b"));
    CHECK(json_end(json));
    fprintf(stderr, "serialized=%s\n", json_output);
    CHECK(strcmp(json_output, "{\"value\":\"a\\\"b\"}") == 0);
    return EXIT_SUCCESS;
}
