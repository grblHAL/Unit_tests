#include "support/json_host.h"
#include <stdint.h>
int main(void)
{
    json_out_t *json = json_start(json_file(), 2);
    CHECK(json != NULL);
    CHECK(json_add_int(json, "value", INT32_MIN));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"value\":-2147483648}") == 0);
    return EXIT_SUCCESS;
}
