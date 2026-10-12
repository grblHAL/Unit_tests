#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^a.c$", "abc") == 1);
    CHECK(match("^a.c$", "ac") == 0);
    CHECK(match("^.$", "") == 0);
    return EXIT_SUCCESS;
}
