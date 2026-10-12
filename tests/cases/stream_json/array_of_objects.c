#include "support/json_host.h"
#include "check.h"

int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_start_array(json, "items"));
    CHECK(json_start_object(json));
    CHECK(json_add_int(json, "value", 1));
    CHECK(json_end_object(json));
    CHECK(json_start_object(json));
    CHECK(json_add_int(json, "value", 2));
    CHECK(json_end_object(json));
    CHECK(json_end_array(json));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"items\":[{\"value\":1},{\"value\":2}]}") == 0);
    return EXIT_SUCCESS;
}
