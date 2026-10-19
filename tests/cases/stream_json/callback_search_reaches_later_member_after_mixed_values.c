#include "support/json_parse_trace_host.h"
int main(void)
{
    char text[] = "{\"first\":42,\"second\":\"text\",\"target\":true}";
    json_stop_tag = "target";
    CHECK(parse_json_trace(text));
    CHECK(json_trace_calls == 3);
    CHECK(strcmp(json_trace_tags[0], "first") == 0 && strcmp(json_trace_values[0], "42") == 0 && !json_trace_strings[0]);
    CHECK(strcmp(json_trace_tags[1], "second") == 0 && strcmp(json_trace_values[1], "text") == 0 && json_trace_strings[1]);
    CHECK(strcmp(json_trace_tags[2], "target") == 0 && strcmp(json_trace_values[2], "true") == 0 && !json_trace_strings[2]);
    return EXIT_SUCCESS;
}
