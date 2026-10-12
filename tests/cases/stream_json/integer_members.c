#include "support/json_host.h"
#include "check.h"

int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_add_int(json, "positive", 42));
    CHECK(json_add_int(json, "negative", -7));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"positive\":42,\"negative\":-7}") == 0);
    return EXIT_SUCCESS;
}
