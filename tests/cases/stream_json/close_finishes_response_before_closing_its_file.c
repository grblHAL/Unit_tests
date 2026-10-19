#include "support/json_host.h"
static unsigned json_close_calls;
static void close_json_response(vfs_file_t *file)
{
    CHECK(file == json_file());
    CHECK(strcmp(json_output, "{\"status\":\"ready\",\"position\":{\"x\":1,\"y\":2}}") == 0);
    json_close_calls++;
}
int main(void)
{
    static const vfs_t backend = {.fwrite = json_write, .fclose = close_json_response};
    vfs_file_t *file = json_file();
    file->fs = &backend;
    json_out_t *json = json_start(file, 4);
    CHECK(json != NULL);
    CHECK(json_add_string(json, "status", "ready"));
    CHECK(json_start_tagged_object(json, "position"));
    CHECK(json_add_int(json, "x", 1));
    CHECK(json_add_int(json, "y", 2));
    CHECK(json_end_object(json));
    CHECK(json_close_calls == 0);
    CHECK(!json_close(NULL));
    CHECK(json_close_calls == 0);
    CHECK(json_close(json));
    CHECK(json_close_calls == 1);
    return EXIT_SUCCESS;
}
