#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^abc$", "abc") == 1);
    CHECK(match("^abc$", "xabc") == 0);
    CHECK(match("^abc$", "abcx") == 0);
    return EXIT_SUCCESS;
}
