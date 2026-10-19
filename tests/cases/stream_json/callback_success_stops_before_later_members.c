#include "support/json_parse_trace_host.h"
int main(void)
{
    char text[] = "{\"target\":42,\"later\":99}";
    json_stop_tag = "target";
    CHECK(parse_json_trace(text));
    CHECK(json_trace_calls == 1 && strcmp(json_trace_values[0], "42") == 0);
    return EXIT_SUCCESS;
}
