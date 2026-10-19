#include "support/json_host.h"
int main(void)
{
    json_out_t *json = json_start(json_file(), 5);
    CHECK(json != NULL);
    CHECK(json_start_array(json, "items"));
    CHECK(json_start_object(json));
    CHECK(json_end_object(json));
    CHECK(json_start_object(json));
    CHECK(json_start_tagged_object(json, "inner"));
    CHECK(json_add_int(json, "value", 7));
    CHECK(json_end_object(json));
    CHECK(json_end_object(json));
    CHECK(json_end_array(json));
    CHECK(json_add_int(json, "done", 1));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"items\":[{},{\"inner\":{\"value\":7}}],\"done\":1}") == 0);
    return EXIT_SUCCESS;
}
