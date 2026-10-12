#include "support/engine_host.h"
#include "vfs.h"
#include "stream_json.h"
#include <string.h>
#include "check.h"
static unsigned calls;
static bool parsed(char *tag, char *value, bool is_string, void *data)
{
    CHECK(data == &calls);
    CHECK(strcmp(tag, "name") == 0);
    CHECK(strcmp(value, "42") == 0);
    CHECK(is_string == false);
    calls++;
    return true;
}
int main(void)
{
    char text[] = "{\"name\":42}";
    CHECK(json_parse_string(text, parsed, &calls));
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
