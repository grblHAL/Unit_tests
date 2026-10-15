#include "support/json_host.h"
#include "support/calloc_failure_host.h"
int main(void)
{
    // Heap exhaustion must not leave a partial JSON response on the file stream.
    fail_calloc = true;
    json_out_t *json = json_start(json_file(), 4);
    fail_calloc = false;
    CHECK(json == NULL && failed_calloc_calls == 1);
    CHECK(json_output[0] == '\0' && json_output_length == 0);
    json = json_start(json_file(), 4);
    CHECK(json != NULL && json_add_string(json, "status", "ready"));
    CHECK(json_end(json));
    CHECK(strcmp(json_output, "{\"status\":\"ready\"}") == 0);
    return EXIT_SUCCESS;
}
