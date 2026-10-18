#include "support/json_parse_trace_host.h"
int main(void)
{
    char text[] = "{\"first\":42,\"second\":false}";
    json_stop_tag = "missing";
    CHECK(!parse_json_trace(text));
    CHECK(json_trace_calls == 2);
    CHECK(strcmp(json_trace_tags[0], "first") == 0 && strcmp(json_trace_tags[1], "second") == 0);
    return EXIT_SUCCESS;
}
