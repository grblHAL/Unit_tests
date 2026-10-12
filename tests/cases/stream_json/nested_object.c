#include "support/json_host.h"
#include "check.h"

int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_start_tagged_object(json, "inner"));
    CHECK(json_add_int(json, "value", 42));
    CHECK(json_end_object(json));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"inner\":{\"value\":42}}") == 0);
    return EXIT_SUCCESS;
}
