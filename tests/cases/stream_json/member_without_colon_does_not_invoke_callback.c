#include "support/json_parse_trace_host.h"
int main(void)
{
    char text[] = "{\"name\"42}";
    CHECK(!parse_json_trace(text));
    CHECK(json_trace_calls == 0);
    char non_json[] = "not-json";
    char unquoted_key[] = "{status:1}";
    CHECK(!parse_json_trace(non_json));
    CHECK(!parse_json_trace(unquoted_key));
    CHECK(json_trace_calls == 0);
    char valid_reply[] = "{\"status\":\"ready\"}";
    json_stop_tag = "status";
    CHECK(parse_json_trace(valid_reply));
    CHECK(json_trace_calls == 1 && json_trace_strings[0]);
    CHECK(strcmp(json_trace_tags[0], "status") == 0);
    CHECK(strcmp(json_trace_values[0], "ready") == 0);
    return EXIT_SUCCESS;
}
