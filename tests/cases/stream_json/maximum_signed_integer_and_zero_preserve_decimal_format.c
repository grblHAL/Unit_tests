#include "support/json_host.h"
#include <stdint.h>
int main(void)
{
    json_out_t *json = json_start(json_file(), 2);
    CHECK(json != NULL);
    CHECK(json_add_int(json, "maximum", INT32_MAX));
    CHECK(json_add_int(json, "zero", 0));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"maximum\":2147483647,\"zero\":0}") == 0);
    return EXIT_SUCCESS;
}
