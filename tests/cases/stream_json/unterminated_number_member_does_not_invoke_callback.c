#include "support/json_parse_trace_host.h"
int main(void)
{
    char text[] = "{\"name\":42";
    CHECK(!parse_json_trace(text));
    CHECK(json_trace_calls == 0);
    return EXIT_SUCCESS;
}
