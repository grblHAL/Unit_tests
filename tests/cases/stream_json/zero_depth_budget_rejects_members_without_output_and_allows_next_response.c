#include "support/json_host.h"
int main(void)
{
    json_out_t *json = json_start(json_file(), 0);
    CHECK(json != NULL && strcmp(json_output, "{") == 0);
    CHECK(!json_add_string(json, "name", "value"));
    CHECK(!json_add_int(json, "count", 2));
    CHECK(!json_add_real(json, "rate", 1.5f, 1));
    CHECK(!json_start_object(json));
    CHECK(!json_start_tagged_object(json, "details"));
    CHECK(!json_start_array(json, "items"));
    CHECK(!json_end_object(json));
    CHECK(!json_end_array(json));
    CHECK(strcmp(json_output, "{") == 0);
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{}") == 0);

    json_output_length = 0;
    json_output[0] = '\0';
    json = json_start(json_file(), 2);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "status", "ready"));
    CHECK(json_start_tagged_object(json, "details"));
    CHECK(json_add_int(json, "count", 2));
    CHECK(json_end_object(json));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"status\":\"ready\",\"details\":{\"count\":2}}") == 0);
    return EXIT_SUCCESS;
}
