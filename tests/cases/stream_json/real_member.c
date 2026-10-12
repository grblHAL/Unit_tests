#include "support/json_host.h"
#include "check.h"

int main(void)
{
    json_out_t *json = json_start(json_file(), 4);
    CHECK(json != NULL);
    CHECK(json_add_real(json, "value", 12.5f, 3));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"value\":12.5}") == 0);
    return EXIT_SUCCESS;
}
